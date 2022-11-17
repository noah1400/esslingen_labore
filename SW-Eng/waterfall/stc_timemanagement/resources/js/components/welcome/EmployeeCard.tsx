import React from 'react';
import { EmployeeProps } from './SupervisorView';

type EmployeeCardProps = {
  employee: EmployeeProps;
  clickHandler: () => void;
  disableNotice?: boolean;
}

export default function EmployeeCard(props: EmployeeCardProps) {
  const {
    employee,
    clickHandler,
    disableNotice = false
  } = props;

  return (
    <div className="px-4 py-4 mx-4 my-4 bg-gray-300 shadow shadow-black bg-opacity-90 hover:bg-opacity-100 hover:cursor-pointer" onClick={ clickHandler }>
      <div className="flex">
        <img
          className="w-auto h-8"
          src="https://tailwindui.com/img/logos/mark.svg?color=indigo&shade=500"
          alt="Your Company" />
        <div className="ml-4">
          <h2>{`ID:${employee.id} / ${employee.name}`}</h2>
          <h2>{employee.position}</h2>
        </div>
      </div>
      {
        !disableNotice &&
        <>
          <div className="flex mt-2">
            <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" className="w-5 h-5 mr-1">
              <path fillRule="evenodd" d="M2.25 12c0-5.385 4.365-9.75 9.75-9.75s9.75 4.365 9.75 9.75-4.365 9.75-9.75 9.75S2.25 17.385 2.25 12zm8.706-1.442c1.146-.573 2.437.463 2.126 1.706l-.709 2.836.042-.02a.75.75 0 01.67 1.34l-.04.022c-1.147.573-2.438-.463-2.127-1.706l.71-2.836-.042.02a.75.75 0 11-.671-1.34l.041-.022zM12 9a.75.75 0 100-1.5.75.75 0 000 1.5z" clipRule="evenodd" />
            </svg>
            <p>Work too muck</p>
          </div>

          <div className="flex mt-1">
            <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24" fill="currentColor" className="w-5 h-5 mr-1">
              <path fillRule="evenodd" d="M2.25 12c0-5.385 4.365-9.75 9.75-9.75s9.75 4.365 9.75 9.75-4.365 9.75-9.75 9.75S2.25 17.385 2.25 12zm11.378-3.917c-.89-.777-2.366-.777-3.255 0a.75.75 0 01-.988-1.129c1.454-1.272 3.776-1.272 5.23 0 1.513 1.324 1.513 3.518 0 4.842a3.75 3.75 0 01-.837.552c-.676.328-1.028.774-1.028 1.152v.75a.75.75 0 01-1.5 0v-.75c0-1.279 1.06-2.107 1.875-2.502.182-.088.351-.199.503-.331.83-.727.83-1.857 0-2.584zM12 18a.75.75 0 100-1.5.75.75 0 000 1.5z" clipRule="evenodd" />
            </svg>
            <p>Need to review worksheet</p>
          </div>

        </>
      }
    </div>

  )
}
