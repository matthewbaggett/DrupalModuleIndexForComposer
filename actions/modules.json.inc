<?php

$app->get('/modules/:version/modules.json', function ($version) {
    $response = array();
    $response['version'] = $version;

    // Response.
    header("Content-type: application/json");
    echo json_pretty(json_encode($response));
    exit;
  }
);
