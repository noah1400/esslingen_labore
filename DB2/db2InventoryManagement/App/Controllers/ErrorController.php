<?php 

namespace App\Controllers;

use Core\Response;
use function Core\dd;

class ErrorController
{
    public function show($request, $code)
    {

        $data = [
            'code' => $code,
            'message' => isset($message) ? $message : $this->getMessage($code),
        ];

        Response::view('errors.error', $data);
    }

    private function getMessage($code)
    {
        $messages = [
            404 => 'Page not found',
            500 => 'Internal server error',
            403 => 'Access denied',
            401 => 'Unauthorized'
        ];

        return $messages[$code] ?? 'Something went wrong';
    }
}