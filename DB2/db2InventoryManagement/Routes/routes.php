<?php

namespace Routes;

use Core\Router;

require 'errors.php';

Router::get('/', 'FirstController@index');
Router::get('/about', 'FirstController@about');
Router::get('/new/route/{id}', 'FirstController@newRoute')->name('newRoute');

Router::get('/parts', 'PartsController@index')->name('parts.index');
Router::get('/parts/create', 'PartsController@create')->name('parts.create');
Router::post('/parts/store', 'PartsController@store')->name('parts.store');
Router::get('/parts/{name}', 'PartsController@show')->name('parts.show');
Router::get('/parts/{name}/edit', 'PartsController@edit')->name('parts.edit');
Router::post('/parts/{name}/update', 'PartsController@update')->name('parts.update');
Router::delete('/parts/{name}/delete', 'PartsController@delete')->name('parts.delete');

