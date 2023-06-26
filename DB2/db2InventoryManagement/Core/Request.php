<?php

namespace Core;

class Request
{

    protected $server;
    protected $request;
    protected $get;
    protected $post;
    protected $input;

    public function __construct() {
        $this->server = $_SERVER;
        $this->request = $_REQUEST;
        $this->get = $_GET;
        $this->post = $_POST;
        
        $input = $this->input();

        // extract keys as varib
    }

    public function uri()
    {
        return trim(parse_url($_SERVER['REQUEST_URI'], PHP_URL_PATH), '/');
    }

    public  function method()
    {
        return $_SERVER['REQUEST_METHOD'];
    }

    public  function all()
    {
        return $_REQUEST;
    }

    public  function input($key = null, $default = null)
    {
        if(is_null($key)) {
            return $this->request;
        }
        return $this->request[$key] ?? $default;
    }

    public  function get($key, $default = null)
    {
        return $this->get[$key] ?? $default;
    }

    public  function post($key, $default = null)
    {
        return $this->post[$key] ?? $default;
    }

    public  function has($key)
    {
        return isset($this->request[$key]);
    }

    public  function only($keys)
    {
        return array_intersect_key($this->request, array_flip((array) $keys));
    }

    public  function except($keys)
    {
        return array_diff_key($this->request, array_flip((array) $keys));
    }

    public function is($type)
    {
        return $this->server['CONTENT_TYPE'] == $type;
    }

    public  function isJson()
    {
        return $this->is('application/json');
    }

    public  function isXml()
    {
        return $this->is('application/xml');
    }

    public  function isHtml()
    {
        return $this->is('text/html');
    }

    public  function isForm()
    {
        return $this->is('application/x-www-form-urlencoded');
    }

    public  function isMultipart()
    {
        return $this->is('multipart/form-data');
    }

    public  function isAjax()
    {
        return isset($this->server['HTTP_X_REQUESTED_WITH']) && $this->server['HTTP_X_REQUESTED_WITH'] == 'XMLHttpRequest';
    }
}