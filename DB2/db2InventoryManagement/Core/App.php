<?php
namespace Core;

class App {
    private static $container;

    // Prevent instantiation, since this is a static class
    private function __construct() {}

    public static function setContainer($container)
    {
        static::$container = $container;
    }

    public static function container()
    {
        return static::$container;
    }

    public static function bind($key, $value)
    {
        static::container()->bind($key, $value);
    }

    public static function resolve($key)
    {
        return static::container()->resolve($key);
    }
}