<?php

namespace Core\Database;
use function Core\config;

class Database {

    protected $pdo;

    public function __construct()
    {

        $type = config('db.connection');
        if ($type == 'sqlite') {
            $this->pdo = new \PDO('sqlite:' . config('db.name'));
        }
        else if ($type == 'sqlsrv')
        {
            $this->pdo = new \PDO(
                config('db.connection') . ':Server=' . config('db.host') . ';Database=' . config('db.name'),
                config('db.username'),
                config('db.password')
            );
        }
        else {
            $this->pdo = new \PDO(
                config('db.connection') . ':host=' . config('db.host') . ';dbname=' . config('db.name'),
                config('db.username'),
                config('db.password')
            );
        }
    }

    public function query($sql, $params = [])
    {
        $stmt = $this->pdo->prepare($sql);
        $stmt->execute($params);
        return $stmt;
    }

    public function row($sql, $params = [])
    {
        $result = $this->query($sql, $params);
        return $result->fetchAll(\PDO::FETCH_ASSOC);
    }

    public function column($sql, $params = [])
    {
        $result = $this->query($sql, $params);
        return $result->fetchColumn();
    }

    public function lastInsertId()
    {
        return $this->pdo->lastInsertId();
    }

}