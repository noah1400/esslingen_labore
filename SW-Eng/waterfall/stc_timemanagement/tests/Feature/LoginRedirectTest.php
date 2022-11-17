<?php

namespace Tests\Feature;

// use Illuminate\Foundation\Testing\RefreshDatabase;
use Tests\TestCase;

class LoginRedirectTest extends TestCase
{
    /**
     * A basic test example.
     *
     * @return void
     */
    public function test_if_user_gets_redirected_to_login()
    {
        $response = $this->get('/');

        $response->assertStatus(302);
    }


}
