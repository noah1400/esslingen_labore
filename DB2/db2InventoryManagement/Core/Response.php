<?php

namespace Core;

class Response {
    
        public static function json($data, $status = 200)
        {
            header('Content-Type: application/json');
            http_response_code($status);
            echo json_encode($data);
        }

        public static function response($data, $status = 200)
        {
            http_response_code($status);
            out($data);
        }
    
        public static function view($view, $data = [])
        {
            //flash
            if (isset($_SESSION['flash'])) {
                $data = array_merge($data, $_SESSION['flash']);
                unset($_SESSION['flash']);
            }

            extract($data);
            $view = str_replace('.', DIRECTORY_SEPARATOR, $view);

            if (!file_exists(\Core\base_path("App\Views\\" . $view . ".view.php"))) {
                abort(404, "View {$view} not found");
                return false;
            }

            require \Core\base_path("App\Views\\" . $view . ".view.php");
            http_response_code(200);
            return true;
        }
    
        public static function redirect($path, $before = null, $data = []) {
            if ($before) {
                $before();
            }

            // pass data to session
            foreach ($data as $key => $value) {
                $_SESSION['flash'][$key] = $value;
            }

            http_response_code($data['status'] ?? 302);
            header("Location: {$path}");
        }


}