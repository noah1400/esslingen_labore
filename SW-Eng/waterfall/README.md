# Deployment on local machine

## Requirements
- PHP `>8.0.0`
Verifiy:
`php -i | findstr /c:"PHP Version => "`
- Nodejs `>16.0.0`
Verify:
`node -v`

## Install php
1. Install [xamp](https://www.apachefriends.org/)
2. Add php installation path to PATH environment variable
    + open xamp control panel ( search in windows start menu )
    + click on the `Explorer` button on the right side
    + navigate to the php installation path `<xamp path>\php` and copy the path
    + search for `env` in the windows start menu click on `Edit Environment variables` or in german `Systemumgebungsvariablen bearbeiten`
    + click on `Environment variables` or `Umgebungsvariablen`
    + double click on the row, in the top table, which says `Path`
    + press `New`
    + paste the php path and click ok

## Install composer
1. Download and run [Composer-Setup.exe](https://getcomposer.org/Composer-Setup.exe)
## Install nodejs
1. Download and run [Nodejs Installer](https://nodejs.org/en/)

## Install dependencies
1. Open terminal
2. Navigate to the `stc_timemanagement` folder
3. Run `composer install`
4. Run `npm install`
## Configure Environment
1. Copy `.env.example` file and paste it as `.env`
2. Open file `.env`
3. Replace
```
DB_CONNECTION=mysql
DB_HOST=127.0.0.1
DB_PORT=3306
DB_DATABASE=laravel
DB_USERNAME=root
DB_PASSWORD=
``` 
with
```
DB_CONNECTION=sqlite
DB_DATABASE=<path to repository>\sw-eng\stc_timemanagement\database\database.sqlite
```
4. Create file `<path to repository>\sw-eng\stc_timemanagement\database\database.sqlite`
## Setup database
1. Run `php artisan migrate`
2. Run `php artisan db:seed --force`

#### 3 Users 
- email: `hr@example.com`, password: `password`, role: `HR`
- email: `su@example.com`, password: `password`, role: `Supervisor`
- email: `em@example.com`, password: `password`, role: `Employee`
## Create Symlink to storage path
1. Run `php artisan storage:link`
## Start webserver
1. Open Terminal
2. Navigate to the project folder
3. Run `php artisan serve`
4. Open second Terminal
5. Navigate to the project folder
6. Run `npm run dev`
5. Open Web Browser and navigate to http://127.0.0.1:8000

# Testing

To run all tests run `php artisan test`
To create new Tests run `php artisan make:test NewTest`

# Create React Elements
1. Create your element `<path to repository>\sw-eng\stc_timemanagement\resources\js\components\MyElement.jsx`
```
import { render } from "react-dom";

export default function MyElement() {
    return(
        <div>MyElement</div>
    )
}

if (document.getElementById('myElement'))
{
    const element = document.getElementById("myElement");
    render(<MyElement \>, element);
}
```
2. Register Element in `<path to repository>\sw-eng\stc_timemanagement\resources\js\app.js`
```
[...]
import './components/MyElement';
```
3. Implement it in .blade.php files
`<div id='myElement'></div>`
 Or in other react elements
 `<MyElement \>`

# Routes

#### GET `/api/v1/users`
+ Requires user to be logged in
+ Returns all users

Example Response:
```
[
  {
    "id": 1,
    "name": "HR",
    "email": "hr@example.com",
    "phone": null,
    "role_id": "1",
    "created_at": "2022-11-16T16:08:52.000000Z",
    "updated_at": "2022-11-16T16:08:52.000000Z"
  },
  {
    "id": 2,
    "name": "Supervisor",
    "email": "su@example.com",
    "phone": null,
    "role_id": "2",
    "created_at": "2022-11-16T16:08:53.000000Z",
    "updated_at": "2022-11-16T16:08:53.000000Z"
  },
  {
    "id": 3,
    "name": "Employee",
    "email": "em@example.com",
    "phone": null,
    "role_id": "3",
    "created_at": "2022-11-16T16:08:53.000000Z",
    "updated_at": "2022-11-16T16:08:53.000000Z"
  }
]
```
+ Returns `403` if user is not logged in

#### GET `/api/v1/employees`

+ Requires user to be logged in
+ Returns all employees

Example Response:
```
[
  {
    "id": 3,
    "name": "Employee",
    "email": "em@example.com",
    "phone": null,
    "role_id": "3",
    "created_at": "2022-11-16T16:08:53.000000Z",
    "updated_at": "2022-11-16T16:08:53.000000Z"
  }
]
```
+ Returns `403` if user is not logged in

#### GET `/api/v1/user`
+ Requires user to be logged in
+ Returns current user

Example Response:
```
{
  "id": 1,
  "name": "Admin",
  "email": "admin@example.com",
  "phone": null,
  "role_id": "1",
  "created_at": "2022-11-07T13:12:30.000000Z",
  "updated_at": "2022-11-07T13:12:30.000000Z"
}
```
+ Returns `403` if user is not logged in
#### GET `/api/v1/user/role`
+ Requires user to be logged in
+ Returns the role of the current User

Example Response:
```
{
  "id": 1,
  "name": "Supervisor",
  "description": "Supervisor",
  "created_at": "2022-11-07T13:12:30.000000Z",
  "updated_at": "2022-11-07T13:12:30.000000Z"
}
```
+ Returns `403` if user is not logged in

#### GET `/api/v1/user/{id}`
+ Requires user to be logged in
+ Returns user with given id
##### Parameter
id: Integer
- id of requested user

Example Response:
`/api/v1/user/1`
```
{
  "id": 1,
  "name": "Admin",
  "email": "admin@example.com",
  "phone": null,
  "role_id": "1",
  "created_at": "2022-11-07T13:12:30.000000Z",
  "updated_at": "2022-11-07T13:12:30.000000Z"
}
```
+ Returns `403` if user is not logged in
+ Returns `404` if user is not found

#### GET `/api/v1/user/{id}/role`
+ Requires the user to be logged in
+ Returns the role of the user with given id
##### Parameter
id: Integer
- id of requested user

Example Response:
`/api/v1/user/1/role`
```
{
  "id": 1,
  "name": "Supervisor",
  "description": "Supervisor",
  "created_at": "2022-11-07T13:12:30.000000Z",
  "updated_at": "2022-11-07T13:12:30.000000Z"
}
```
- Returns `403` if user is not logged in
- Returns `404` if user is not found

#### GET `/api/v1/role/{id}/users`
+ Requires the user to be logged in
+ Returns all users with a specific role

##### Parameter
id: Integer
- id of requested role

Example Response:
`/api/v1/role/1/users`
```
[
  {
    "id": 1,
    "name": "Admin",
    "email": "admin@example.com",
    "phone": null,
    "role_id": "1",
    "created_at": "2022-11-07T13:12:30.000000Z",
    "updated_at": "2022-11-07T13:12:30.000000Z"
  }
]
```
- Returns `403` if user is not logged in
- Returns `404` if role is not found

#### GET `/api/v1/role/{id}`
+ Requires user to be logged in
+ Returns role with given id

##### Parameter
id: integer
- id of requested role

Example Response:
`/api/v1/role/1`
```
[
  {
    "id": 1,
    "name": "Supervisor",
    "description": "Supervisor",
    "created_at": "2022-11-07T13:12:30.000000Z",
    "updated_at": "2022-11-07T13:12:30.000000Z"
  }
]
```
- Returns `403` if user is not logged in
- Returns `404` if role is not found

#### GET `/api/v1/roles`
- Requires user to be logged in
- Returns all roles

Example Response:
```
[
  {
    "id": 1,
    "name": "Supervisor",
    "description": "Supervisor",
    "created_at": "2022-11-07T13:12:30.000000Z",
    "updated_at": "2022-11-07T13:12:30.000000Z"
  },
  {
    "id": 2,
    ...
  }
]
```
- Returns `403` if user is not logged in

#### GET `/user/create`

- requires user to be logged in
- shows form to create a user
- Returns `403` if user is not logged

#### POST `/user/create`

- requires user to be logged in
- creates new user

##### Body

- name: `string,max:255`
- email: `required|email|unique:users`
- password: `required|string`
- password_confirmation: `required|same(password)`
- role: `required|string|exists:roles,name`


- Validation of Parameters done in backend
- Returns `403` if user is not logged in

#### GET `/api/v1/user/entry/{date}`

- requires user to be logged in
- returns worksheet entry on given date

##### Parameter
- date: `date|required|format:YYYY-MM-DD`

Example Response: `/api/v1/user/entry/2022-11-16`
```
{
  "id": 0,
  "user_id": 0,
  "date": "2022-11-16",
  "start_time": "8:00",
  "end_time": "16:00",
  "break_time": "30",
  "hours_target": "8",
  "hours_as_is": "8",
  "absence_id": null,
}
```

All time values a probably returned as milliseconds or ISO timestamps, hasn't been tested yet.

- return `403` if user is not logged in

#### GET `/api/v1/user/{id}/entries/{date}`

- requires user to be logged in
- returns worksheet entry on given date

##### Parameter
- id: `integer|required`
- date: `date|required|format:YYYY-MM-DD`


Example Response: `/api/v1/user/1/entry/2022-11-16`
```
{
  "id": 1,
  "user_id": 1,
  "date": "2022-11-16",
  "start_time": "8:00",
  "end_time": "16:00",
  "break_time": "30",
  "hours_target": "8",
  "hours_as_is": "8",
  "absence_id": null,
}
```

All time values a probably returned as milliseconds or ISO timestamps, hasn't been tested yet.

- return `403` if user is not logged in

#### GET `/user/entry/create/{date}`

- user needs to be logged in
- Shows form to create a new entry at given date
##### Parameter
- date: `date_format:YYYY-MM-DD`


- Returns `403` user is not logged in

#### POST `/user/entry/create`

- user needs to be logged in
- creates new entry
##### Body

- date: `required|date|date_format:Y-m-d`
- start_time: `date_format:H:i`
- end_time: `date_format:H:i`
- break_time: `date_format:H:i`
- hours_target: `date_format:H:i`
- hours_as_is: `date_format:H:i`
- absence_id: `exists:absences,id`

- returns `403` if user is not logged in

#### GET `/user/entry/edit/{date}`

- user needs to be logged in
- Shows form to edit entry

##### Parameter

-date: `date_format:YYYY-MM-DD`

- returns `403` if user is not logged in
- returns `404` if entry is not found

#### POST `/user/entry/edit`

- user needs to be logged in
- Updates existing entry

##### Body

- date: `required|date|date_format:Y-m-d`
- start_time: `date_format:H:i`
- end_time: `date_format:H:i`
- break_time: `date_format:H:i`
- hours_target: `date_format:H:i`
- hours_as_is: `date_format:H:i`

- returns `403` if user is not logged in

#### GET `/api/v1/user/entries/{year}/{month}`

- user needs to be logged in
- returns all entries of logged in user in given year and month

##### Parameter
- year: string with format `YYYY`
- month: string with format `MM`

Example Response: `/api/v1/user/entries/2022/11`
```
[
  {
    "id": 1,
    "user_id": 1,
    "date": "2022-11-1",
    "start_time": "8:00",
    "end_time": "16:00",
    "break_time": "30",
    "hours_target": "8",
    "hours_as_is": "8",
    "absence_id": null
  },
  {
    ...
  }
]
```

- returns `403` if user is not logged in

#### GET `/api/v1/user/{id}/entries/{year}/{month}`

- user needs to be logged in
- returns all entries of user with given id in given year and mmonth

##### Parameter
- id: Integer
- year: string with format `YYYY`
- month: string with format `MM`

Example Response `/api/v1/user/2/entries/2022/11`
```
[
  {
    "id": 15,
    "user_id": 2,
    "date": "2022-11-4",
    "start_time": "8:00",
    "end_time": "17:00",
    "break_time": "30",
    "hours_target": "8",
    "hours_as_is": "9",
    "absence_id": null
  },
  {
    ...
  }
]
```

# Tables

## Syntax

```
Schema::create('< table name >', function (Blueprint $table) {
    $table->< data type >('< column name >')
})
```

Additional functions:
`nullable()`: column can be null ( not filled )
`unique()`: no other entry can have the same value in this column
`default(< value >)`: if row does not get set on inserting new entry a default value will be set.

## `users` Table
```
Schema::create('users', function (Blueprint $table) {
    $table->id();
    $table->string('name');
    $table->string('email')->unique();
    $table->string('phone')->nullable();
    $table->string('password');
    $table->string('position');
    $table->foreignId('role_id')->constrained('roles');
    $table->rememberToken();
    $table->timestamps();
});
```

## `worksheet_entries` Table
```
Schema::create('worksheets_entries', function(Blueprint $table) {
    $table->id();
    $table->foreignId('user_id')->constrained('users'); // User to which the entry belongs
    $table->date('date'); // Date of the entry
    $table->time('start_time')->nullable(); // Start time of the entry
    $table->time('end_time')->nullable(); // End time of the entry
    $table->time('break_time')->nullable(); // Break time of the entry
    $table->time('hours_target')->nullable(); // Target hours of the entry
    $table->time('hours_as_is')->nullable(); // As-is hours of the entry
    $table->foreignId('absence_id')->nullable()->constrained('absences'); // Absence of the entry
    $table->timestamps();
});
```

## `roles` Table
```
Schema::create('roles', function(Blueprint $table) {
    $table->id();
    $table->string('name'); // Name of the role
    $table->string('description')->nullable(); // Description of the role
    $table->timestamps();
});
```

## `absences` Table
```
Schema::create('absences', function(Blueprint $table) {
    $table->id();
    $table->string('name'); // Name of the absence
    $table->string('description')->nullable(); // Description of the absence
    $table->boolean('is_sick')->default(false); // Is the absence sick?
    $table->boolean('is_vacation')->default(false); // Is the absence vacation?
    $table->boolean('is_travel')->default(false); // Is the absence travel?
    $table->boolean('is_flextime')->default(false); // Is the absence flextime?
    $table->timestamps();
});
```