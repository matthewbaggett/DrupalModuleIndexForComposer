<?php

$app->get('/modules/:version/modules.json', function ($version) {
    $version_codes['6.x'] = 87;
    $version_codes['7.x'] = 103;
    $version_codes['8.x'] = 7234;

    $response = array();
    $response['version'] = $version;

    $url = DRUPAL_MODULE_INDEX;
    $url = str_replace("%PROJECT_STATUS%", 0, $url);
    $url = str_replace("%DRUPAL_VERSION%", $version_codes[$version], $url);

    $cache_file = '../cache/' . basename($url);

    if(!file_exists($cache_file) || filemtime($cache_file) < strtotime('10 minutes ago')){
        $http_client = new Guzzle\Http\Client();
        $http_request = $http_client->get($url);
        $http_response = $http_request->send();
        $http_body = $http_response->getBody();
        file_put_contents($cache_file,$http_body);
        $response['from_cache'] = 'no';
    }else{
        $http_body = file_get_contents($cache_file);
        $response['from_cache'] = 'yes';
    }

    $dom = new SimpleHtmlDom\SimpleHtmlDom();
    $dom->load($http_body);
    $found_modules = $dom->find('.view-project-index .view-content .item-list ol li .views-field-title .field-content a');

    $response['packages'] = array();
    foreach($found_modules as $found_module){
        $name = "drupal" . str_replace("project/","",$found_module->href);
        $package = new Package();
        $response['packages'][$name] = array(
            $package->version => $package
        );
    }

    // Response.
    header("Content-type: application/json");
    echo json_pretty(json_encode($response));
    exit;
  }
);
