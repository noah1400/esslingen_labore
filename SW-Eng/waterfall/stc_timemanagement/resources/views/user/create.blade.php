@extends('layouts.app')

@section('content')

@if ($errors->any())
    <div class="alert alert-danger">
        <ul>
            @foreach ($errors->all() as $error)
                <li>{{ $error }}</li>
            @endforeach
        </ul>
    </div>
@endif
@if ( session('success') )
    <div class="alert alert-success">
        <p>{{ session('success') }} </p>
    </div>
@endif

<div class="container mx-auto">
<h1 class="mt-10 text-2xl text-center">New User</h1>
<form action="{{ url('/user/create') }}" method="post" class="w-full max-w-sm mx-auto mt-10">
    @csrf

    <div class="mb-6 md:flex md:items-center">
      <div class="md:w-1/3">
        <label class="block pr-4 mb-1 font-bold text-gray-500 md:text-right md:mb-0" for="name">Name</label>
      </div>
      <div class="md:w-2/3">
        <input class="w-full px-4 py-2 leading-tight text-gray-700 bg-gray-200 border-2 border-gray-200 rounded appearance-none focus:outline-none focus:bg-white focus:border-purple-500" type="text" name="name" id="name" value="{{ old('name') }}">
      </div>
    </div>

    <div class="mb-6 md:flex md:items-center">
      <div class="md:w-1/3">
        <label class="block pr-4 mb-1 font-bold text-gray-500 md:text-right md:mb-0" for="email">Email</label>
      </div>
      <div class="md:w-2/3">
        <input class="w-full px-4 py-2 leading-tight text-gray-700 bg-gray-200 border-2 border-gray-200 rounded appearance-none focus:outline-none focus:bg-white focus:border-purple-500" type="text" name="email" id="email" value="{{ old('email') }}">
      </div>
    </div>

    <div class="mb-6 md:flex md:items-center">
      <div class="md:w-1/3">
        <label class="block pr-4 mb-1 font-bold text-gray-500 md:text-right md:mb-0" for="position">Position</label>
      </div>
      <div class="md:w-2/3">
        <input class="w-full px-4 py-2 leading-tight text-gray-700 bg-gray-200 border-2 border-gray-200 rounded appearance-none focus:outline-none focus:bg-white focus:border-purple-500" type="text" name="position" id="position" value="{{ old('position') }}">
      </div>
    </div>

    <div class="mb-6 md:flex md:items-center">
      <div class="md:w-1/3">
        <label class="block pr-4 mb-1 font-bold text-gray-500 md:text-right md:mb-0" for="password">Password</label>
      </div>
      <div class="md:w-2/3">
        <input class="w-full px-4 py-2 leading-tight text-gray-700 bg-gray-200 border-2 border-gray-200 rounded appearance-none focus:outline-none focus:bg-white focus:border-purple-500" type="password" name="password" id="password">
      </div>
    </div>

    <div class="mb-6 md:flex md:items-center">
      <div class="md:w-1/3">
        <label class="block pr-4 mb-1 font-bold text-gray-500 md:text-right md:mb-0" for="password_confirmation">Password Confirmation</label>
      </div>
      <div class="md:w-2/3">
        <input class="w-full px-4 py-2 leading-tight text-gray-700 bg-gray-200 border-2 border-gray-200 rounded appearance-none focus:outline-none focus:bg-white focus:border-purple-500" type="password" name="password_confirmation" id="password_confirmation">
      </div>
    </div>

    <div class="mb-6 md:flex md:items-center">
      <div class="md:w-1/3">
        <label class="block pr-4 mb-1 font-bold text-gray-500 md:text-right md:mb-0" for="role">Role</label>
      </div>
      <div class="md:w-2/3">
        <select class="w-full px-4 py-2 leading-tight text-gray-700 bg-gray-200 border-2 border-gray-200 rounded appearance-none focus:outline-none focus:bg-white focus:border-purple-500" name="role" id="role">
            <option value="HR">HR</option>
            <option value="Supervisor">Supervisor</option>
            <option value="Employee">Employee</option>
        </select>
      </div>
    </div>

    <div class="flex justify-around">
      <button class="px-4 py-2 font-bold text-white bg-purple-500 rounded shadow hover:bg-purple-400 focus:shadow-outline focus:outline-none" type="submit">Create</button>
    </div>
    <a class="block mt-2 text-center text-blue-500 underline" href="/">Go back homepage</a>
</form>
</div>

@endsection
