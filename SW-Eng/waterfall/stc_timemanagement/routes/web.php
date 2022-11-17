<?php

use Illuminate\Support\Facades\Route;
use App\Http\Controllers\UserController;
use App\Http\Controllers\RoleController;
use App\Http\Middleware\loggedIn;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

Route::get('/', function () {
    return view('welcome');
})->middleware('auth');

Auth::routes();


Route::group(['middleware' => ['loggedIn']], function () {
    /**
     * Api routes
     */
    /**
     * Returns all users
     */
    Route::get('/api/v1/users', [UserController::class, 'getUsers']);
    /**
     * Returns employees
     */
    Route::get('/api/v1/employees', [UserController::class, 'getEmployees']);
    /**
     * Returns the current user
     */
    Route::get('/api/v1/user', [UserController::class, 'getUser']);
    /**
     * Returns the roles of the current user
     */
    Route::get('/api/v1/user/role', [UserController::class, 'getUserRole']);
    /**
     * Returns the user with the given id
     */
    Route::get('/api/v1/user/{id}', [UserController::class, 'getUserById']);
    /**
     * Returns the role of the user with the given id
     */
    Route::get('/api/v1/user/{id}/role', [UserController::class, 'getUserRoleById']);
    /**
     * Returns all users with the given role
     */
    Route::get('/api/v1/role/{id}/users', [RoleController::class, 'getUsersByRole']);
    /**
     * Returns the role with the given id
     */
    Route::get('/api/v1/role/{id}', [RoleController::class, 'getRoleById']);
    /**
     * Returns all roles
     */
    Route::get('/api/v1/roles', [RoleController::class, 'getRoles']);
    /**
     * Returns worksheet entry of the current user of the given date
     * Date format: YYYY-MM-DD
     */
    Route::get('/api/v1/user/entry/{date}', [UserController::class, 'getEntryByDate']);

    /**
     * Returns worksheet entries of the user with the given id of the given month
     */
    Route::get('/api/v1/user/{id}/entries/{date}', [UserController::class, 'getEntryById']);
    /**
     * Returns all entries of current user in given month
     */
    Route::get('/api/v1/user/entries/{year}/{month}', [UserController::class, 'getEntriesByMonth']);
    /**
     * Returns all entries of user with given id in given month
     */
    Route::get('/api/v1/user/{id}/entries/{year}/{month}', [UserController::class, 'getEntriesByIdByMonth']);



    /**
     * Web routes
     */

     /**
      * Shows form to create a new user
      */
    Route::get('/user/create', [UserController::class, 'createUser']);
    /**
     * Creates a new user
     */
    Route::post('/user/create', [UserController::class, 'storeUser']);
    /**
     * Shows form to edit the current user
     */
    Route::get('/user/edit/{id}', [UserController::class, 'editUser']);
    /**
     * Edits the current user
     */
    Route::post('/user/edit/{id}', [UserController::class, 'updateUser']);
    /**
     * Shows form to create new entry
     */
    Route::get('/user/entry/create/{date}', [UserController::class, 'createEntry']);
    /**
     * Creates new entry
     */
    Route::post('/user/entry/create', [UserController::class, 'storeEntry']);
    /**
     * Shows form to edit entry
     */
    Route::get('/user/entry/edit/{date}', [UserController::class, 'editEntry']);
    /**
     * Edits entry
     */
    Route::post('/user/entry/edit', [UserController::class, 'updateEntry']);


});


