import React, { useState, useEffect } from 'react';
import EmployeeCard from './EmployeeCard';
import Axios from '../../axios';
import { EmployeeProps } from './SupervisorView';

export default function HR() {
  const [employees, setEmployees] = useState<EmployeeProps[]>([])
  const [currentEmployee, setCurrentEmployee] = useState<EmployeeProps>()
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

  return (
    <div className="min-h-screen pt-5 pb-5 bg-gray-100">
      <div className="mx-auto max-w-7xl grid grid-cols-3 gap-x-5">
        <div className="max-h-[80vh] overflow-y-auto bg-white border border-gray-400 col-span-1">
          <div
            className="px-4 py-4 mx-4 my-4 bg-gray-300 shadow shadow-black bg-opacity-90 hover:bg-opacity-100 hover:cursor-pointer"
            onClick={ () => {
              location.href = '/user/create'
            }
          }>
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" strokeWidth={5} stroke="#6466F1" className="w-6 h-6 mx-auto">
              <path strokeLinecap="round" strokeLinejoin="round" d="M12 4.5v15m7.5-7.5h-15" />
            </svg>

          </div>

          {
            employees.map(employee => (
              <EmployeeCard employee={employee} key={employee.id} clickHandler={() => setCurrentEmployee(employee)} disableNotice={true} />
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

            <button
              type="button"
              onClick={ () => alert('We have not yet implemented this feature') }
              className="inline-flex items-center rounded border border-transparent bg-indigo-100 px-2.5 py-1.5 text-xs font-medium text-indigo-700 hover:bg-indigo-200 focus:outline-none focus:ring-2 focus:ring-indigo-500 focus:ring-offset-2 absolute bottom-12 right-20"
            >
              Register for Sickness
            </button>
          </div>
        </div>
      </div>
    </div>
  );
}
