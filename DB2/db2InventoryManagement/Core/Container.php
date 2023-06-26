<?php

namespace Core;

class Container
{
    protected $bindings = [];

    protected $instances = [];

    public function bind($key, $value)
    {
        $this->bindings[$key] = $value;
    }

    public function resolve($key)
    {
        if (isset($this->bindings[$key])) {

            if (static::hasInstance($key)) {
                return $this->instances[$key];
            }
            $ret = call_user_func($this->bindings[$key]);
            if (is_object($ret)) {
                $this->instances[$key] = $ret;
            }
            return $ret;
        }else{
            throw new \Exception("No {$key} is bound in the container.");
        }
    }

    public function instance($key, $value)
    {
        $this->instances[$key] = $value;
    }

    public function has($key)
    {
        return isset($this->bindings[$key]);
    }

    public function hasInstance($key)
    {
        return isset($this->instances[$key]);
    }

    public function reset($key = null)
    {
        if ($key) {
            unset($this->instances[$key]);
        }else{
            $this->instances = [];
        }
    }
}