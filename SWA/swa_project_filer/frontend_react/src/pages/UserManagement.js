import React, { useContext, useEffect, useState } from 'react'
import NavigationComponent from '../components/Navigation';
import SideNav from '../components/SideNav';
import UserItem from '../components/items/UserItem';
import AuthContext from "../components/shared/AuthContext";
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faPlus } from '@fortawesome/free-solid-svg-icons';
import dayjs from 'dayjs';

const Usermanagement = () => {
    const { getallusers, signup } = useContext(AuthContext);
    const [users, setUsers] = useState(new Array());
    const [firstname, setFirstName] = useState("");
    const [lastname, setLastName] = useState("");
    const [dob_, setDob] = useState("");
    const [email_, setEmail] = useState("");
    const [role_, setRole] = useState("");
    const [password, setPassword] = useState("");

    useEffect(() => {
        getallusers().then((result) => {
            setUsers(result.data);
        }).catch((err) => {
           console.log(err); 
        });
    });

    async function createUser() {
        let payload = {
            email: email_,
            firstName: firstname,
            lastName: lastname,
            role: role_,
            dateOfBirth: dayjs(dob_).format("DD.MM.YYYY"),
            password: password
          };
          await signup(payload).then((result) => {
            window.location.reload();
          });
    }

    return (
        <>
            <div className='vh-100'>
                <NavigationComponent />
                <div className='row w-100 content-fill'>
                    <SideNav/>
                    <div className='col-10'>
                        <nav className='w-100 px-4 py-2 mt-2 text-center'>
                            <div className='d-flex flex-column text-decoration-underline ls-wide'>
                                <h3>User management</h3>
                            </div>
                            <div className='d-flex ls-wide'>
                                <label htmlFor='createDir' className='btn btn-outline-primary rounded-0 px-4' role='button' data-bs-toggle="modal" data-bs-target={"#createUser"}>
                                    <FontAwesomeIcon icon={faPlus} className='me-2'/>
                                        Create User
                                </label>
                                <input type='button' className='d-none' id="createDir"/>
                            </div>
                        </nav>
                        <div className='row border-bottom mb-2 m-0 mx-2 py-2'>
                            <div className='col-2'><p className='mb-0 fw-semibold text-capitalize'>first name</p></div>
                            <div className='col-2'><p className='mb-0 fw-semibold text-capitalize'>last name</p></div>
                            <div className='col-3'><p className='mb-0 fw-semibold text-capitalize'>email</p></div>
                            <div className='col-2'><p className='mb-0 fw-semibold text-capitalize'>date of birth</p></div>
                            <div className='col-2'><p className='mb-0 fw-semibold text-capitalize'>role</p></div>
                        </div>
                        {/* File List Items*/}
                        <div className='row m-0 mx-2'>
                            {users.map((value, key) => {
                                return <UserItem key={key} index={value.id} fname={value.firstName} lname={value.lastName} email={value.email} dob={value.dateOfBirth} role={value.role} />
                            })}
                        </div>
                    </div>
                </div>
            </div>
            
            { /* ----------  Edit User Info  ---------- */ }
            <div className="modal fade" id={"createUser"} aria-labelledby={"createUser"} aria-hidden="true">
                <div className="modal-dialog">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id={"createUser"}>Edit User</h5>
                            <button type="button" className="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div className="modal-body">
                            <div className="mb-3">
                                <label htmlFor="firstname" className="form-label text-start w-100">First name</label>
                                <input type="text" className="form-control py-2" onChange={(e) => setFirstName(e.target.value)} id="firstname" required/>
                            </div>
                            <div className="mb-3">
                                <label htmlFor="lastname" className="form-label text-start w-100">Last name</label>
                                <input type="text" className="form-control py-2" onChange={(e) => setLastName(e.target.value)} id="lastname" required/>
                            </div>
                            <div className="mb-3">
                                <label htmlFor="dob" className="form-label text-start w-100">Date of birth</label>
                                <input type="date" className="form-control py-2" onChange={(e) => setDob(e.target.value)} id="dob" required/>
                            </div>
                            <div className="mb-3">
                                <label htmlFor="password" className="form-label text-start w-100">Password</label>
                                <input type="password" className="form-control py-2" onChange={(e) => setPassword(e.target.value)} id="password" required/>
                            </div>
                            <div className="mb-3">
                                <label htmlFor="email" className="form-label text-start w-100">Email</label>
                                <input type="text" className="form-control py-2" onChange={(e) => setEmail(e.target.value)} id="email" required/>
                            </div>
                            <div className="mb-3">
                                <label className="form-label text-start w-100">Role</label>
                                <select className="form-select" aria-label="User Role" onChange={(e) => setRole(e.target.value)} >
                                  <option defaultChecked hidden>Select User Role</option>
                                  <option value="standard">User</option>
                                  <option value="admin">Admin</option>
                                </select>
                            </div>
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-subtle" data-bs-dismiss="modal">Cancel</button>
                            <button type="button" className="btn btn-primary" onClick={createUser}>Create User</button>
                        </div>
                    </div>
                </div>
            </div>
        </>
    );
}

export default Usermanagement;