import React, { useContext, useState } from 'react'
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faEllipsis, faTrashCan, faEdit } from '@fortawesome/free-solid-svg-icons';
import { Dropdown } from 'react-bootstrap';
import dayjs from "dayjs";
import AuthContext from '../shared/AuthContext';

const UserItem = ({index, fname, lname, email, dob, role}) => {
    const [firstname, setFirstName] = useState(fname);
    const [lastname, setLastName] = useState(lname);
    const [email_, setEmail] = useState(email);
    const [dob_, setDob] = useState(dob);
    const [role_, setRole] = useState(role);
    const { edituser } = useContext(AuthContext);    

    async function updateUser() {
        let payload = {
          email: email_,
          firstName: firstname,
          lastName: lastname,
          role: role_,
          dateOfBirth: dayjs(dob_).format("DD.MM.YYYY")
        };
        await edituser(index, payload);
    }

    return (  
        <>
            <div className='col-12 row m-0 mb-1 py-2 p-0'>
                <div className='col-2 d-flex align-items-center p-0'>
                    <p className='ms-3 text-dark mb-0'>{fname}</p>
                </div>
                <div className='col-2 d-flex align-items-center p-0'>
                    <p className='ms-3 text-dark mb-0'>{lname}</p>
                </div>
                <div className='col-3 d-flex align-items-center p-0'>
                    <p className='ms-3 text-dark mb-0'>{email}</p>
                </div>
                <div className='col-2 d-flex align-items-center p-0'>
                    <p className='ms-3 text-dark mb-0'>{dayjs(dob).format("DD.MM.YYYY")}</p>
                </div>
                <div className='col-2 d-flex align-items-center p-0'>
                    <p className='ms-3 text-dark mb-0 text-capitalize'>{role}</p>
                </div>
                <div className='col-1 d-flex align-items-center'>
                    <button className='btn' data-bs-toggle="modal" data-bs-target={"#edituser-"+index}><FontAwesomeIcon icon={faEdit}/> Change</button>
                </div>
            </div>
            { /* ----------  Edit User Info  ---------- */ }
            <div className="modal fade" id={"edituser-"+index} aria-labelledby={"edituser-"+index} aria-hidden="true">
                <div className="modal-dialog">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id={"edituser-"+index}>Edit User</h5>
                            <button type="button" className="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div className="modal-body">
                            <div className="mb-3">
                                <label htmlFor={"firstname-"+index} className="form-label text-start w-100">First name</label>
                                <input type="text" className="form-control py-2" value={firstname} onChange={(e) => setFirstName(e.target.value)} id={"firstname-"+index} required/>
                            </div>
                            <div className="mb-3">
                                <label htmlFor={"lastname-"+index} className="form-label text-start w-100">Last name</label>
                                <input type="text" className="form-control py-2" value={lastname} onChange={(e) => setLastName(e.target.value)} id={"lastname-"+index} required/>
                            </div>
                            <div className="mb-3">
                                <label htmlFor="dob" className="form-label text-start w-100">Date of birth</label>
                                <input type="date" className="form-control py-2" value={dob_} onChange={(e) => setDob(e.target.value)} id="dob" required/>
                            </div>
                            <div className="mb-3">
                                <label htmlFor={"email-"+index} className="form-label text-start w-100">Email</label>
                                <input type="text" className="form-control py-2" value={email_} onChange={(e) => setEmail(e.target.value)} id={"email-"+index} required/>
                            </div>
                            <div className="mb-3">
                                <label className="form-label text-start w-100">Role</label>
                                <select className="form-select" aria-label="User Role" value={role_} onChange={(e) => setRole(e.target.value)} >
                                  <option defaultChecked hidden>Select User Role</option>
                                  <option value="STDT_USER">User</option>
                                  <option value="admin">Admin</option>
                                </select>
                            </div>
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-subtle" data-bs-dismiss="modal">Cancel</button>
                            <button type="button" className="btn btn-primary" onClick={updateUser} data-bs-dismiss="modal">Update</button>
                        </div>
                    </div>
                </div>
            </div>
        </>
    );
}

export default UserItem;