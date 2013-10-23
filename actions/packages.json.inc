<?php

$app->get('/packages.json', function () {
    $response = array();
    $response['notify'] = "/downloads/%package%";
    $response['notify_batch'] = "/downloads";
    $response['packages'] = array();
    $response['includes'] = array();
    $response['includes']['modules/6x/modules.json'] = array();
    $response['includes']['modules/7x/modules.json'] = array();
    $response['includes']['modules/8x/modules.json'] = array();

    // Response.
    header("Content-type: application/json");
    echo json_pretty(json_encode($response));
    exit;
});


