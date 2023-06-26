<?php

// register the autoloader

spl_autoload_register(function ($class) {

    $namespaces = [
            
            'Core' => 'Core',
    
            'App' => 'App',
            
            'Routes' => 'Routes'
    
        ];
    foreach ($namespaces as $namespace => $path) {

        if (strpos($class, $namespace) === 0) {

            $class = str_replace($namespace, '', $class);

            $class = str_replace('\\', DIRECTORY_SEPARATOR, $class);
            $class = str_replace('/', DIRECTORY_SEPARATOR, $class);

            $class = ltrim($class, '/');

            $file = __DIR__ . "/../{$path}/{$class}.php";

            if (file_exists($file)) {

                require $file;

            }

        }

    }
});