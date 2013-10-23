<?php
require_once("../configure.inc");
require_once("../lib/json_pretty.inc");
require_once("../vendor/autoload.php");

$app = new \Slim\Slim();

require_once("../actions/info.inc");
require_once("../actions/modules.json.inc");
require_once("../actions/packages.json.inc");
require_once("../actions/index.inc");

$app->run();