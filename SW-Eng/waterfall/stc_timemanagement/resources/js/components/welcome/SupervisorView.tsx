import React, { useState, useEffect } from 'react';
import EmployeeCard from './EmployeeCard';
import Axios from '../../axios';

export type EmployeeProps = {
  id: number;
  name: string;
  position: string;
}

export type CurrentEmployeeDetailProps = {
  id: number;
  user_id: number;
  date: string;
  start_time: string;
  end_time: string;
  break_time: number;
  hours_target: number
  hours_as_is: number
  absence_id: number|null,
}

export default function Supervisor() {

  const [employees, setEmployees] = useState<EmployeeProps[]>([])
  const [currentEmployee, setCurrentEmployee] = useState<EmployeeProps>()
  const [currentEmployeeDetail, setCurrentEmployeeDetail] = useState<CurrentEmployeeDetailProps>()
  useEffect(() => {
    const fetchEmployeesData = async () => {
      const result = await Axios.get(
        '/api/v1/employees'
      );

      const employees = result.data
      setEmployees(employees)
      employees && setCurrentEmployee(employees[0])
    };

    fetchEmployeesData();
  }, [])

  useEffect(() => {
    const fetchEmployeeData = async () => {
      const now = new Date();
      const today = `${now.getFullYear()}-${now.getMonth()}-${now.getDay()}`
      const result = await Axios.get(
        `/api/v1/user/entry/${today}`
      );
      setCurrentEmployeeDetail(result.data)
    };

    fetchEmployeeData();

  }, [currentEmployee])

  return (
    <div className="min-h-screen pt-5 pb-5 bg-gray-100">
      <div className="mx-auto max-w-7xl grid grid-cols-3 gap-x-5">
        <div className="max-h-[80vh] overflow-y-auto bg-white border border-gray-400 col-span-1">
          {
            employees.map(employee => (
              <EmployeeCard employee={employee} key={employee.id} clickHandler={() => setCurrentEmployee(employee)} />
              ))
          }
        </div>

        <div className="relative px-2 bg-white border border-gray-400 col-span-2">
          <div className="px-4 py-4">
            <div className="flex items-center">
              <img
                className="w-auto h-32"
                src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=500"
                alt="Your Company" />
              <div className="ml-8">
                {
                  currentEmployee &&
                  <>
                    <h2 className="text-2xl">{`ID:${currentEmployee.id} / ${currentEmployee.name}`}</h2>
                    <h2 className="text-lg">{currentEmployee.position}</h2>
                  </>
                }
              </div>
            </div>

            <div className="flex justify-around mt-8">
              <div className="w-48 py-2 text-center bg-white border border-gray-400">
                <h3 className="text-lg">Flex Time</h3>
                <p className="text-center text-md">+2 HR</p>
              </div>
              <div className="w-48 py-2 text-center bg-white border border-gray-400">
                <h3 className="text-lg">Vacation Days</h3>
                <p className="text-center text-md">25/0/30</p>
              </div>
              <div className="w-48 py-2 text-center bg-white border border-gray-400">
                <h3 className="text-lg">Break Time</h3>
                <p className="text-center text-md">30 Min</p>
              </div>
            </div>

            <div className="flex items-center justify-center mt-24">
              <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" className="w-5 h-5 mr-1">
                <path fillRule="evenodd" d="M2.25 12c0-5.385 4.365-9.75 9.75-9.75s9.75 4.365 9.75 9.75-4.365 9.75-9.75 9.75S2.25 17.385 2.25 12zm8.706-1.442c1.146-.573 2.437.463 2.126 1.706l-.709 2.836.042-.02a.75.75 0 01.67 1.34l-.04.022c-1.147.573-2.438-.463-2.127-1.706l.71-2.836-.042.02a.75.75 0 11-.671-1.34l.041-.022zM12 9a.75.75 0 100-1.5.75.75 0 000 1.5z" clipRule="evenodd" />
              </svg>
              <p className="text-xl">Last day working hours: 16hr</p>
            </div>

            <button
              type="button"
              onClick={ () => alert('We have not yet implemented this feature') }
              className="inline-flex items-center rounded border border-transparent bg-indigo-100 px-2.5 py-1.5 text-xs font-medium text-indigo-700 hover:bg-indigo-200 focus:outline-none focus:ring-2 focus:ring-indigo-500 focus:ring-offset-2 absolute bottom-12 right-20"
            >
              Review Worksheet
            </button>
          </div>
        </div>
      </div>
    </div>

  );
}
