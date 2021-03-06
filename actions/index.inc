<?php
function examplify($pattern) {

  $pattern = str_replace("(/:response_mode)", "/json", $pattern);
  return $pattern;
}

$app->get(
  '/',
  function () use ($app) {
    $template = <<<EOT
<!DOCTYPE html>
    <html>
        <head>
            <meta charset="utf-8"/>
            <title>Drupal Modules for Composer</title>
            <style type="text/css" media="all">
              @import url("layout/css/default.css");
            </style>
        </head>
        <body>
            <header>
                <a href="#">Drupal Modules for Composer</a>
            </header>
            <section>
                <h2>Endpoints</h2>
                <ul>
                  %%ENDPOINTS%%
                </ul>
                <div class="clear"></div>
            </section>

        </body>
    </html>
EOT;

    // Hack out the routes from the Slim underlaying system using reflection
    $myClassReflection = new ReflectionClass(get_class($app->router()));
    $secret = $myClassReflection->getProperty('routes');
    $secret->setAccessible(true);

    // Generate routes array
    $routes = array();
    $endpoints_html = array();
    foreach ($secret->getValue($app->router()) as $route) {
      /* @var $route \Slim\Route */
      $key = trim($route->getPattern());
      $routes[$key] = $route;
    }

    // Sort the Routes
    ksort($routes);

    // Display the routes
    foreach ($routes as $route) {
      /* @var $route \Slim\Route */

      $example = ltrim(examplify($route->getPattern()), '/');
      $dir = rtrim(dirname($_SERVER['SCRIPT_NAME']), '/') . '/';
      $example_url = "http://" . $_SERVER['SERVER_NAME'] . $dir . str_replace("/json", "/human", $example);
      $methods = implode(" | ", $route->getHttpMethods());

      // Build HTML
      $endpoint_html = array();
      $endpoint_html[] = "<dl>";
      $endpoint_html[] = "  <dt>Name</dt>";
      $endpoint_html[] = "  <dd>{$route->getName()}</dd>";
      $endpoint_html[] = "  <dt>Pattern</dt>";
      $endpoint_html[] = "  <dd>{$methods} {$route->getPattern()}</dd>";
      $endpoint_html[] = "  <dt>Example</dt>";
      $endpoint_html[] = "  <dd><a href=\"{$example_url}\">/{$example}</a></dd>";
      $endpoint_html[] = "</dl>";

      $endpoints_html[] = implode('', $endpoint_html);
    }

    $template = str_replace('%%ENDPOINTS%%', "<li>" . implode("</li><li>", $endpoints_html) . "</li>", $template);
    echo $template;
  }
);
