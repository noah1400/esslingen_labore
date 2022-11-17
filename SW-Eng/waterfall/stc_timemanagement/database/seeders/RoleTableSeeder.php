<?php

namespace Database\Seeders;

use Illuminate\Database\Console\Seeds\WithoutModelEvents;
use Illuminate\Database\Seeder;
use App\Models\Role;

class RoleTableSeeder extends Seeder
{
    /**
     * Run the database seeds.
     *
     * @return void
     */
    public function run()
    {
        // create new Role
        $role = new Role(
            [
                'name' => 'HR',
                'description' => 'Human Resources'
            ]
        );
        $role->save();
        $role = new Role(
            [
                'name' => 'Supervisor',
                'description' => 'Supervisor'
            ]
        );
        $role->save();
        $role = new Role(
            [
                'name' => 'Employee',
                'description' => 'Employee'
            ]
        );
        $role->save();
    }
}
