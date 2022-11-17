import { render } from "react-dom";
import React, { useEffect, useState } from 'react';
import Axios from '../../axios';
import Employee from "./EmployeeView";
import Supervisor from "./SupervisorView";
import HR from "./HRView";
import NavBar from "../utilities/NavBar";

export type UserProps = {
  id: number
  name: string
  email: string
  phone: string
  role_id: number
  created_at: string
  updated_at: string
}

export type RoleProps = {
  id: number
  name: string
  description: string
}


const initUserData = {
  id: 0,
  name: "",
  email: "",
  phone: "",
  role_id: 1,
  created_at: "",
  updated_at: ""
}

export default function Welcome() {

  const [currentRoleId, setCurrentRoleId] = useState<number>(1);
  const [user, setUser] = useState<UserProps>(initUserData);
  const [roles, setRoles] = useState<RoleProps[]>([]);
  const getRoleName = (id:number): string | null => {
    return roles.find(role => role.id == id)?.name
  }

  useEffect(() => {
    const fetchUserData = async () => {
      const result = await Axios.get(
        '/api/v1/user'
      );

      const user: UserProps = result.data;
      setUser(user);
      setCurrentRoleId(user.role_id)
    };

    const fetchRolesData = async () => {
      const result = await Axios.get(
        '/api/v1/roles'
      );

      setRoles(result.data);
    };

    fetchUserData();
    fetchRolesData();
  }, [])

  const renderRoleSelector = () => {
    return  (
      <>
        {
          getRoleName(user.role_id) === 'Supervisor'?
          <select className="py-0 border-0" onChange={ event => setCurrentRoleId(Number(event.target.value)) } defaultValue={currentRoleId}>
            {roles.filter(role => (role.name != 'HR')).map(role => (
              <option value={role.id} key={role.id}>
                { role.name }
              </option>
            ))}
          </select>:getRoleName(user.role_id)
        }
      </>
    )
  }

  return (
    <>
      <NavBar id={user.id} >
        { renderRoleSelector() }
      </NavBar>
      {getRoleName(currentRoleId) === 'Employee' && <Employee />}
      {getRoleName(currentRoleId) === 'Supervisor' && <Supervisor />}
      {getRoleName(currentRoleId) === 'HR' && <HR />}
</>
    );
}

const welcome = document.getElementById("welcome");
if (welcome) {
  render(<Welcome />, welcome);
}
