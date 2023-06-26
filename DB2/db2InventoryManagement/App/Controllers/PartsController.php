<?php 

namespace App\Controllers;
use Core\App;
use Core\Response;

use function Core\dd;
use function Core\abort;
use function Core\request;

class PartsController {

    public function index()
    {
        $db = App::resolve('Core\Database\Database');
        $stmt = $db->query('SELECT * FROM noscit00_GetAllParts()');
        $result = $stmt->fetchAll(\PDO::FETCH_ASSOC);
        $parts = array_map(function($part) {
            return (object) $part;
        }, $result);
        Response::view('parts.index', compact('parts'));
    }

    public function show($request, $name)
    {
        $db = App::resolve('Core\Database\Database');
        $stmt = $db->query("SELECT * FROM noscit00_GetPartByName(?)", [$name]);
        $result = $stmt->fetch(\PDO::FETCH_ASSOC);
        if (!$result) {
            abort(404, 'Part not found');
        }
        $part = (object) $result;
        Response::view('parts.show', compact('part'));
    }

    public function edit($request, $name)
    {
        $db = App::resolve('Core\Database\Database');
        $stmt = $db->query("SELECT * FROM noscit00_GetPartByName(?)", [$name]);
        $result = $stmt->fetch(\PDO::FETCH_ASSOC);
        if (!$result) {
            abort(404, 'Part not found');
        }
        $part = (object) $result;
        Response::view('parts.edit', compact('part'));
    }

    public function update($request, $name)
    {
        $db = App::resolve('Core\Database\Database');
        $stmt = $db->query("SELECT * FROM noscit00_GetPartByName(?)", [$name]);
        $result = $stmt->fetch(\PDO::FETCH_ASSOC);
        if (!$result) {
            abort(404, 'Part not found');
        }
        $part = (object) $result;
        $part->name = $request->has('name') ? $request->input('name') : $part->name;
        $part->description = $request->has('description') ? $request->input('description') : $part->description;
        $part->category = $request->has('category') ? $request->input('category') : $part->category;

        $stmt = $db->query("EXEC noscit00_UpdatePart ?, ?, ?, ?", [
            $part->name,
            $part->description,
            $part->category,
            $part->id
        ]);
        Response::redirect('/parts');
    }

    public function create()
    {
        Response::view('parts.create');
    }

    public function store($request)
    {
        $db = App::resolve('Core\Database\Database');
        $stmt = $db->query("EXEC noscit00_addpart ?, ?, ?", [
            $request->input('name'),
            $request->input('description'),
            $request->input('category')
        ]);
        Response::redirect('/parts');
    }
}