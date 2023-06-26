<?php

namespace Core;

function abort($code = 404, $message = null)
{
    if (is_null($message)) {
        $messages = [
            400 => 'Bad Request',
            401 => 'Unauthorized',
            403 => 'Forbidden',
            404 => 'Not Found',
            405 => 'Method Not Allowed',
            500 => 'Internal Server Error',
            503 => 'Service Unavailable',
        ];

        $message = $messages[$code] ?? 'Unknown Error';
    }

    http_response_code($code);

    // get file in which this function is called
    $trace = debug_backtrace();
    $file = $trace[0]['file'];
    $line = $trace[0]['line'];

    $message = "Error {$code}: {$message} in {$file} on line {$line}";

    echo $message;
    exit;
}

function base_path($path = '')
{
    $path = str_replace('/', DIRECTORY_SEPARATOR, $path);
    $path = str_replace('\\', DIRECTORY_SEPARATOR, $path);
    return __DIR__ . DIRECTORY_SEPARATOR . '..' . DIRECTORY_SEPARATOR . $path;

}

function config($key = null, $default = null)
{

    // key can be a.b.c
    // return config['a']['b']['c']

    static $config;

    if (is_null($config)) {
        $config = require base_path('config.php');
    }

    if (is_null($key)) {
        return $config;
    }

    $keys = explode('.', $key);

    $value = $config;

    foreach ($keys as $key) {
        if (isset($value[$key])) {
            $value = $value[$key];
        } else {
            return $default;
        }
    }

    return $value;
}

function request($key = null, $default = null)
{
    $request = new Request();

    if (is_null($key)) {
        return $request;
    }

    return $request->input($key, $default);
}

function dd($data)
{
    echo '<pre>';
    print_r($data);
    echo '</pre>';

    $file = debug_backtrace()[0]['file'];
    $line = debug_backtrace()[0]['line'];

    echo "Called from {$file} on line {$line}";

    http_response_code(200);
    exit;
}

function debug($data)
{
    if (config('debug') == 'true') {
        echo '<pre>';
        print_r($data);
        echo '</pre>';
    }
}

function routePath($name) {
    $routes = Router::routes();

    foreach ($routes as $route) {
        if ($route->getName() == $name) {
            return $route->getUri();
        }
    }

    return null;
}

function route($name, $params = []) {
    $path = routePath($name);

    if (is_null($path)) {
        return null;
    }

    foreach ($params as $key => $value) {
        $path = str_replace("{{$key}}", $value, $path);
    }

    return $path;
}

function url($path = '') {
    $url = config('url');
    $url = trim($url, '/');
    $path = trim($path, '/');
    return $url . '/' . $path;
}

function out($data) {
    echo htmlentities($data, ENT_QUOTES, 'UTF-8');
}

function outNoEscape($data) {
    echo $data;
}

function asset($path) {

    $html = "";

    // if ends with .css
    // add <link> tag

    if (substr($path, -4) == '.css') {
        $html = "<link rel='stylesheet' href='" . url('assets/'.$path) . "'>";
    } else if (substr($path, -3) == '.js') {
        $html = "<script src='" . url('assets/'.$path) . "'></script>";
    }

    echo $html;
}

function view($path) {
    $path = str_replace('.', DIRECTORY_SEPARATOR, $path);
    $path = base_path('App/Views/' . $path . '.view.php');

    if (file_exists($path)) {
        require $path;
    } else {
        abort(404, "View {$path} not found");
    }
}