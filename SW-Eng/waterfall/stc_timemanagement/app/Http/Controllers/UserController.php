<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Models\User;
use App\Models\Role;
use Illuminate\Support\Facades\Hash;

class UserController extends Controller
{
    /**
     * Returns all users
     */
    public function getUsers() {
        return User::all();
    }
    /**
     * Returns employees
     */
    public function getEmployees() {
        return User::where('role_id', 3)->get();
    }
    /**
     * Returns the current user
     *
     * @return \Illuminate\Http\Response
     */
    function getUser() {
        return response()->json(auth()->user());
    }

    /**
     * Returns the user with the given id
     */
    function getUserById($id) {
        return response()->json(User::findOrFail($id));
    }

    /**
     * Returns the role of the current user
     */
    function getUserRole() {
        return response()->json(auth()->user()->role);
    }

    /**
     * Returns the role of the user with the given id
     */
    function getUserRoleById($id) {
        return response()->json(User::findOrFail($id)->role);
    }

    /**
     * Returns view for form to create a new user
     */
    function createUser() {
        return view('user.create');
    }
    /**
     * Creates a new user
     */
    function storeUser(Request $request) {
        $request->validate([
            'name' => 'required|string|max:255',
            'email' => 'required|email|unique:users',
            'position' => 'required|string|max:255',
            'password' => 'required|string|confirmed',
            'role' => 'required|exists:roles,name'
        ]);
        $role = Role::where('name', $request->get('role'))->first();
        $rid = $role->id;

        $user = new User([
            'name' => $request->get('name'),
            'email' => $request->get('email'),
            'position' => $request->get('position'),
            'password' => Hash::make($request->get('password'))
        ]);
        $user->role_id = $rid;
        $user->save();
        return redirect('/user/create')->with('success', 'User saved!');
    }
    /**
     * Returns view for form to edit the user with the given id
     */
    function editUser($id) {
        $user = User::findOrFail($id);
        return view('user.edit', compact('user'));
    }
    /**
     * Updates the user with the given id
     */
    function updateUser(Request $request, $id) {
        $request->validate([
            'name' => 'required|string|max:255',
            'email' => 'required|email|unique:users,email,'.$id,
            'password' => 'required|confirmed',
            'role' => 'required|exists:roles,name'
        ]);
        $user = User::findOrFail($id);
        $user->name = $request->get('name');
        $user->email = $request->get('email');
        $user->password = Hash::make($request->get('password'));
        $role = Role::where('name', $request->get('role'))->first();
        $rid = $role->id;
        $user->role_id = $rid;
        $user->save();
        return redirect('/user/edit/' . $id)->with('success', 'User updated!');
    }
    /**
     * Returns entries of the current user of given date
     */
    function getEntryByDate($date) {
        $entry = auth()->user()->entries()->where('date', $date)->get();
        return response()->json($entry);
    }
    /**
     * Returns entries of the user with the given id of the given date
     * @param int $id
     * @param string $date
     * Date in format YYYY-MM-DD
     */
    function getEntryById($id, $date) {
        $user = User::findOrFail($id);
        return response()->json($user->entries()->where('date', $date)->first());
    }
    /**
     * Shows form to create a new entry for the current user
     */
    function createEntry($date) {
        return view('entry.create', compact('date'));
    }
    /**
     * Creates a new entry for the current user
     */
    function storeEntry(Request $request) {

        $request->validate([
            'date' => 'required|date|date_format:Y-m-d',
            'start_time' => 'date_format:H:i',
            'end_time' => 'date_format:H:i',
            'break_time' => 'date_format:H:i',
            'hours_target' => 'date_format:H:i',
            'hours_as_is' => 'date_format:H:i',
            'absence_id' => 'exists:absences,id',
        ]);

        $user = auth()->user();
        $entry = $user->entries()->where('date', $request->get('date'))->first();

        if ($entry == null) {
            $entry = $user->entries()->create([
                'date' => $request->get('date'),
                'user_id' => $user->id,
                'start_time' => $request->get('start_time'),
                'end_time' => $request->get('end_time'),
                'break_time' => $request->get('break_time'),
                'hours_target' => $request->get('hours_target'),
                'hours_as_is' => $request->get('hours_as_is'),
                'absence_id' => $request->get('absence_id')
            ]);
        } else {
            $entry->start_time = $request->get('start_time');
            $entry->end_time = $request->get('end_time');
            $entry->break_time = $request->get('break_time');
            $entry->hours_target = $request->get('hours_target');
            $entry->hours_as_is = $request->get('hours_as_is');
            $entry->absence_id = $request->get('absence_id');
            $entry->save();
        }

        return redirect('/user/entry/create/' . $request->get('date'))->with('success', 'Entry saved!');
    }

    /**
     * Shows form to edit the entry of the current user of the given date
     */
    function editEntry($date) {
        $entry = auth()->user()->entries()->where('date', $date)->first();
        return view('entry.edit', compact('entry'));
    }

    /**
     * Updates the entry of the current user of the given date
     */
    function updateEntry(Request $request) {
        $request->validate([
            'date' => 'required|date|date_format:Y-m-d',
            'user_id' => 'required|exists:users,id',
            'start_time' => 'date_format:H:i',
            'end_time' => 'date_format:H:i',
            'break_time' => 'date_format:H:i',
            'hours_target' => 'date_format:H:i',
            'hours_as_is' => 'date_format:H:i',
            'absence_id' => 'exists:absences,id',
        ]);

        $user = User::findOrFail($request->get('user_id'));
        $entry = $user->entries()->where('date', $request->get('date'))->first();

        if ($entry == null) {
            $entry = $user->entries()->create([
                'date' => $request->get('date'),
                'user_id' => $request->get('user_id'),
                'start_time' => $request->get('start_time'),
                'end_time' => $request->get('end_time'),
                'break_time' => $request->get('break_time'),
                'hours_target' => $request->get('hours_target'),
                'hours_as_is' => $request->get('hours_as_is'),
                'absence_id' => $request->get('absence_id')
            ]);
        } else {
            $entry->start_time = $request->get('start_time');
            $entry->end_time = $request->get('end_time');
            $entry->break_time = $request->get('break_time');
            $entry->hours_target = $request->get('hours_target');
            $entry->hours_as_is = $request->get('hours_as_is');
            $entry->absence_id = $request->get('absence_id');
            $entry->save();
        }

        return redirect('/user/entry/edit/' . $request->get('date'))->with('success', 'Entry updated!');
    }

    function getEntriesByMonth($month, $year) {
        $entries = auth()->user()->entries()->whereMonth('date', $month)->whereYear('date', $year)->get();
        return response()->json($entries);
    }

    function getEntriesByIdByMonth($id, $month, $year) {
        $user = User::findOrFail($id);
        $entries = $user->entries()->whereMonth('date', $month)->whereYear('date', $year)->get();
        return response()->json($entries);
    }
}
