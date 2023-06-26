<?php

namespace Core;

class Route {

    protected $uri = "";

    protected $controller = "";

    protected $action = "";

    protected $params = [];

    protected $method = "";

    protected $name = "";

    protected $middleware = [];

    public function __construct($uri, $controller, $action, $method="GET", $name=null, $middleware=[])
    {
        $this->uri = $uri;
        $this->controller = $controller;
        $this->action = $action;
        $this->method = $method;
        $this->name = $name;
        $this->middleware = $middleware;
    }

    public function match($uri, $method)
    {

        debug("Matching route: {$this->uri} with {$uri} and {$method}");

        if ($this->method != $method) {
            return false;
        }

        $pattern = preg_replace('/\//', '\/', $this->uri);
        $pattern = preg_replace('/\{([a-z]+)\}/', '(?P<\1>[A-Za-z0-9\$\-_\.\+!\*\'\(\)]+)', $pattern);
        $pattern = '/^' . $pattern . '$/i';

        debug("Pattern: {$pattern}");

        if (preg_match($pattern, $uri, $matches)) {
            foreach ($matches as $key => $match) {
                if (is_string($key)) {
                    $this->params[$key] = $match;
                }
            }
            return true;
        }

        return false;
    }

    public function getUri()
    {
        return $this->uri;
    }

    public function getController()
    {
        return $this->controller;
    }

    public function getAction()
    {
        return $this->action;
    }

    public function getParams()
    {
        return $this->params;
    }

    public function getMethod()
    {
        return $this->method;
    }

    public function getName()
    {
        return $this->name;
    }

    public function getMiddleware()
    {
        return $this->middleware;
    }

    public function call() {
        $c = "App\\Controllers\\{$this->controller}";

        $c = new $c;

        if (!method_exists($c, $this->action)) {
            $cName = get_class($c);
            abort(404, "{$cName} does not respond to the {$this->action} action.");
        }

        return $c->{$this->action}(request(), ...array_values($this->params));

    }

    public function name($name)
    {
        $this->name = $name;
        return $this;
    }

}