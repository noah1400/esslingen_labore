<?php

use Core\Router;

Router::get('/error/{code}', 'ErrorController@show');