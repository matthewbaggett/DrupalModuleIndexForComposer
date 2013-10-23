<?php
$app->get(
  '/Info',
  function () use ($app) {
    phpinfo();
    exit;
  }
);