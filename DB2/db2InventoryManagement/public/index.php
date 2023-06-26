<?php

use Core\Router;

use function Core\base_path;
require '../bootstrap.php';
require base_path('Routes/routes.php');

Router::dispatch();