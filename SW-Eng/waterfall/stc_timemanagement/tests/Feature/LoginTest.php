<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Support\Facades\Hash;
use App\Models\User;
use App\Models\Role;
use Illuminate\Foundation\Testing\WithFaker;
use Tests\TestCase;

class LoginTest extends TestCase
{
    use RefreshDatabase;

    /**
     * A basic feature test example.
     *
     * @return void
     */
    public function test_if_login_is_successfull()
    {
        $this->seed();

        // login with the user
        $user = User::where('email', 'hr@example.com')->first();

        $response = $this->post('/login', [
            'email' => 'hr@example.com',
            'password' => 'password'
        ]);

        // assert that the user is logged in
        $response->assertRedirect('/');
        $this->assertAuthenticatedAs($user);
    }
}
