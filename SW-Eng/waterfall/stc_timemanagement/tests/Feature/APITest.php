<?php

namespace Tests\Feature;

use Illuminate\Foundation\Testing\RefreshDatabase;
use Illuminate\Foundation\Testing\WithFaker;
use Tests\TestCase;
use App\Models\User;
use App\Models\Role;

class APITest extends TestCase
{
    use RefreshDatabase;
    /**
     * A basic feature test example.
     *
     * @return void
     */
    public function test_if_api_routes_are_accessible()
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

        // test the api
        $response = $this->get('/api/v1/users');
        $response->assertStatus(200);

        $response = $this->get('/api/v1/user');
        $response->assertStatus(200);
        $response->assertContent($user->toJson());

        $response = $this->get('/api/v1/user/role');
        $response->assertStatus(200);
        $response->assertContent($user->role->toJson());

        $response = $this->get('/api/v1/user/' . $user->id . '/role');
        $response->assertStatus(200);
        $response->assertContent($user->role->toJson());

        $response = $this->get('/api/v1/roles');
        $response->assertStatus(200);
        $response->assertJsonCount(3);
        $response->assertContent(Role::all()->toJson());

        $response = $this->get('/api/v1/role/' . $user->role->id);
        $response->assertStatus(200);
        $response->assertContent($user->role->toJson());

        $response = $this->get('/api/v1/role/' . $user->role->id . '/users');
        $response->assertStatus(200);
        $response->assertJsonCount(1);
        $response->assertContent($user->role->users->toJson());

        $response = $this->get('/api/v1/user/entry/2021-01-01');
        $response->assertStatus(200);
        $response->assertContent($user->entries->toJson());


    }
}
