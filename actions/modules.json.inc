<?php

$app->get('/modules/:version/modules.json', function ($version) {
    $response = array();
    $response['version'] = $version;

    // Response.
    header("Content-type: application/json");
    $jsonPretty = new \webignition\JsonPrettyPrinter\JsonPrettyPrinter();
    echo $jsonPretty->format(json_encode($response));
    exit;
  }
);
