<?php

namespace App\Controllers;
use Core\Response;
use Core\App;

use function Core\abort;
use function Core\request;

class FirstController
{
    public function index($request)
    {
        $db = App::resolve('Core\Database\Database');
        Response::view('notes.index', [
            'name' => request('name','John Doe'),
        ]);
    }

    public function about()
    {
        Response::view('notes.about', [
            'name' => 'John Doe',
            'age' => 30,
        ]);
    }

    public function newRoute($request, $id)
    {
        Response::view('notes.newRoute', [
            'name' => 'John Doe',
            'age' => 30,
            'id' => $id,
        ]);
    }
}