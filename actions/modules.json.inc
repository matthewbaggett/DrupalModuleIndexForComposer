<?php

$app->get('/modules/:version/modules.json', function ($version) {
    $response = array();
    $response['version'] = $version;

    // Response.
    header("Content-type: application/json");
    $jsonPretty = new Camspiers\JsonPretty\JsonPretty;
    echo $jsonPretty->prettify($response);
    exit;
  }
);
