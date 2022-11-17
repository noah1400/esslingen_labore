<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\Role;

class RoleController extends Controller
{
    /**
     * Returns all users with the given role
     */
    function getUsersByRole($id) {
        return response()->json(Role::findOrFail($id)->users);
    }

    /**
     * Returns the role with the given id
     */
    function getRoleById($id) {
        return response()->json(Role::findOrFail($id));
    }

    /**
     * Returns all roles
     */
    function getRoles() {
        return Role::all();
    }
}
