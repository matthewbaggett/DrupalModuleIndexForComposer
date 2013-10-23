<?php

$app->get('/packages.json', function ($name) {
    echo "Hello, $name";
});