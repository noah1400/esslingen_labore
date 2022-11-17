import { Disclosure } from '@headlessui/react'
import { BellIcon } from '@heroicons/react/24/outline'
import React from "react";
import Axios from '../../axios';

type NavBarProps = {
  id: number;
  children: React.ReactElement;
}

const NavBar = (props: NavBarProps) => {
  const {
    id
  } = props;

  return (
    <Disclosure as="nav" className="bg-white">
      <div className="px-2 mx-auto max-w-7xl sm:px-6 lg:px-8">
        <div className="relative flex items-center justify-between h-16">
          <div className="flex items-center justify-center flex-1 sm:items-stretch sm:justify-start">
            <div className="flex items-center flex-shrink-0">
              <img
                className="block w-auto h-8 lg:hidden"
                src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=500"
                alt="Your Company" />
              <img
                className="hidden w-auto h-8 lg:block"
                src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=500"
                alt="Your Company" />
              <h1 className="ml-4 text-xl text-gray-400">SW-Eng Project</h1>
            </div>
          </div>
          <div className="flex items-center pr-2 sm:static sm:inset-auto sm:ml-6 sm:pr-0">
            <button
              type="button"
              className="p-1 text-gray-400 bg-gray-800 rounded-full hover:text-white focus:outline-none focus:ring-2 focus:ring-white focus:ring-offset-2 focus:ring-offset-gray-800"
            >
              <span className="sr-only">View notifications</span>
              <BellIcon className="w-6 h-6" aria-hidden="true" />
            </button>
            <p className="px-2 py-2 ml-4 border border-gray-800">ID: {id}</p>
            <p className="px-2 py-2 ml-4 border border-gray-800">Role:
              {props.children}
            </p>
            <button className="px-2 py-2 ml-4 border border-gray-800 hover:bg-red-500 hover:text-white" onClick={() => {
              Axios.post('/logout');
              location.href = "/";
            }}>
              Logout
            </button>
          </div>
        </div>
      </div>
    </Disclosure>
  )
}

export default NavBar;
