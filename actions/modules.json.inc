<?php

$app->get('/modules/:version/modules.json', function ($version) {
    $version_codes['6.x'] = 87;
    $version_codes['7.x'] = 103;
    $version_codes['8.x'] = 7234;

    $response = array();
    $response['version'] = $version;

    $url = DRUPAL_MODULE_INDEX;
    $url = str_replace("%DRUPAL_VERSION%", 0, $url);
    $url = str_replace("%PROJECT_STATUS%", $version_codes[$version], $url);

    $client = new Guzzle\Http\Client('https://api.github.com');
    $request = $client->get($url);
    $response = $request->send();

    $dom = new SimpleHtmlDom\SimpleHtmlDom();
    $dom->load($response->getBody());


    // Response.
    header("Content-type: application/json");
    echo json_pretty(json_encode($response));
    exit;
  }
);
