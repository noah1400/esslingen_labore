<?php

namespace Database\Seeders;

use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use App\Models\User;
use Illuminate\Support\Facades\Hash;

class UsersTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        $user = new User([
            'name' => 'HR',
            'email' => 'hr@example.com',
            'password' => Hash::make('password'),
            'position' => 'HR',
            'role_id' => 1
        ]);
        $user->save();
        $user = new User([
            'name' => 'Supervisor',
            'email' => 'su@example.com',
            'password' => Hash::make('password'),
            'position' => 'Supervisor|Software Engineer',
            'role_id' => 2
        ]);
        $user->save();
        $user = new User([
            'name' => 'Employee',
            'email' => 'em@example.com',
            'password' => Hash::make('password'),
            'position' => 'Software Engineer',
            'role_id' => 3
        ]);
        $user->save();

        // Create dummy users
        User::factory()->count(15)->create();
    }
}
