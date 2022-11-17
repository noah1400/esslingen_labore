@extends('layouts.app')

@section('content')
<div id="login" route="{{ route('login') }}" token="{{ csrf_token() }}"></div>
@endsection
