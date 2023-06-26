<?php

namespace Core;

class Router
{

    protected static $routes = [];

    private static function addRoute($method, $uri, $controller)
    {

        $v = explode('@', $controller);
        $controller = $v[0];
        $action = $v[1];

        $method = strtoupper($method);

        $route = new Route($uri, $controller, $action, $method);
        static::$routes[] = $route;

        return $route;
    }

    public static function get($uri, $controller)
    {
        return static::addRoute('GET', $uri, $controller);
    }

    public static function post($uri, $controller)
    {
        return static::addRoute('POST', $uri, $controller);
    }

    public static function delete($uri, $controller)
    {
        return static::addRoute('DELETE', $uri, $controller);
    }

    public static function put($uri, $controller)
    {
        return static::addRoute('PUT', $uri, $controller);
    }

    public static function patch($uri, $controller)
    {
        return static::addRoute('PATCH', $uri, $controller);
    }

    public static function direct($uri, $requestType)
    {
        $route = static::getMatchedRoute($uri, $requestType);

        if ($route) {
            return static::callAction($route);
        }

        abort(404, 'No route defined for URI ' . $uri . ' and request type ' . $requestType . '.');
    }

    protected static function callAction($route)
    {
        return $route->call();
    }

    public static function dispatch()
    {

        // if resource is requested return file as is
        if (preg_match('/\.(?:png|jpg|jpeg|gif|css|js)$/', $_SERVER["REQUEST_URI"])) {
            return false;
        }

        $uri = parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH);
        $uri = $uri ?: '/';

        return static::direct($uri, $_SERVER['REQUEST_METHOD']);
    }

    public static function routes($method = null)
    {
        if ($method) {
            $method = strtoupper($method);
            $rs = [];
            foreach (static::$routes as $route) {
                if ($route->method == $method) {
                    $rs[] = $route;
                }
            }
            return $rs;
        }
        return static::$routes;
    }

    private static function getMatchedRoute($uri, $method)
    {
        foreach (static::$routes as $route) {
            if ($route->match($uri, $method)) {
                return $route;
            }
        }
        return false;
    }
}
