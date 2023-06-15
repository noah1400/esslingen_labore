import React, { useContext, useEffect, useState } from 'react'
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faEllipsis, faTrashCan, faEdit, faPlus } from '@fortawesome/free-solid-svg-icons';
import { Dropdown } from 'react-bootstrap';
import AuthContext from "../shared/AuthContext";
import MemberItem from './MemberItem';
import dayjs from "dayjs";

const GroupItem = ({id, name, founder, created}) => {    
    const { getgroupmembers, getallusers, addusertogroups, deletegroups, editgroup } = useContext(AuthContext);
    const [name_, setName] = useState(name);
    const [member, setMember] = useState("");
    const [users, setUsers] = useState(new Array());
    const [members, setMembers] = useState(new Array());

    useEffect(() => {
        getgroupmembers(id).then((result) => {
            setMembers(result.data);
        });
        getallusers().then((result) => {
            setUsers(result.data);
        }).catch((err) => {
           console.log(err); 
        });
    }, []);

    async function deleteGroup() {
        await deletegroups(id);
        window.location.reload();
    }
    async function addMember() {
        await addusertogroups(member, id);
        window.location.reload();
    }
    async function editGroup() {
        let payload = {
            groupname: name_,
            email: member,
        };
        await editgroup(id, payload);
        window.location.reload();
    }
    return (  
        <>
            <div className="accordion-item col-12">
                <h2 className="accordion-header" id="headingOne">
                <button className="accordion-button" data-bs-toggle="collapse" data-bs-target="#collapseOne" aria-expanded="false" aria-controls="collapseOne">
                    <div className='col-12 row m-0 mb-1 py-2 p-0'>
                        <div className='col-4 d-flex align-items-center p-0'>
                            <p className='ms-3 text-dark mb-0'>{name}</p>
                        </div>
                        <div className='col-4 d-flex align-items-center p-0'>
                            <p className='ms-3 text-dark mb-0'>{founder}</p>
                        </div>
                        <div className='col-3 d-flex align-items-center p-0'>
                            <p className='ms-3 text-dark mb-0'>{dayjs(created).format("DD.MM.YYYY")}</p>
                        </div>
                        <div className='col-1 d-flex align-items-center'>
                            <Dropdown>
                                <Dropdown.Toggle className="bg-white border-0 p-0" variant='light' id="dropdown-basic">
                                <span className='btn rounded-0 btn-subtle'><FontAwesomeIcon icon={faEllipsis}/></span>
                                </Dropdown.Toggle>

                                <Dropdown.Menu className='rounded-0'>
                                <Dropdown.Item className='text-neutral-700' data-bs-toggle="modal" data-bs-target={"#editgroup-"+id}><FontAwesomeIcon icon={faEdit}/> Edit</Dropdown.Item>
                                <Dropdown.Item className='text-neutral-700' data-bs-toggle="modal" data-bs-target={"#adduser-"+id}><FontAwesomeIcon icon={faPlus}/> Add Member</Dropdown.Item>
                                <Dropdown.Item className='text-red-200' data-bs-toggle="modal" data-bs-target={"#deleteuser-"+id}><FontAwesomeIcon icon={faTrashCan} /> Delete</Dropdown.Item>
                                </Dropdown.Menu>
                            </Dropdown>
                        </div>
                    </div>
                </button>
                </h2>
                <div id="collapseOne" className="accordion-collapse collapse border-top bg-light" aria-labelledby="headingOne" data-bs-parent="#accordion">
                    <div className="m-0 mx-2 py-2 w-100 text-center">
                        <h3><u>Members</u></h3>
                    </div>
                    <div className="accordion-body px-3">
                        <div className='row mb-2 m-0 mx-2 py-2'>
                            <div className='col-2'><p className='mb-0 fw-semibold text-capitalize'>first name</p></div>
                            <div className='col-2'><p className='mb-0 fw-semibold text-capitalize'>last name</p></div>
                            <div className='col-3'><p className='mb-0 fw-semibold text-capitalize'>email</p></div>
                            <div className='col-2'><p className='mb-0 fw-semibold text-capitalize'>date of birth</p></div>
                            <div className='col-3'><p className='mb-0 fw-semibold text-capitalize'>role</p></div>
                            <div className='col-1'><p className='mb-0 fw-semibold text-capitalize'>role</p></div>
                        </div>
                        
                    {/* File List Items*/}
                    <div className="accordion row m-0 mx-2" id="accordion">
                        {members.map((value, key) => {
                            return <MemberItem key={key} index={value.id} fname={value.firstName} lname={value.lastName} email={value.email} dob={value.dateOfBirth} role={value.role} groupid={id}/>
                        })}
                    </div>
                    </div>
                </div>
            </div>
            { /* ----------  Edit Group  ---------- */ }
            <div className="modal fade" id={"editgroup-"+id} aria-labelledby={"editgroup-"+id} aria-hidden="true">
                <div className="modal-dialog">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id={"editgroup-"+id}>Add Member</h5>
                            <button type="button" className="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div className="modal-body">
                            <div className="mb-3">
                                <label htmlFor="dirname" className="form-label text-start w-100">Group name</label>
                                <input type="text" className="form-control py-2" onChange={(e) => setName(e.target.value)} id="dirname" required/>
                            </div>
                            <div className="mb-3">
                                <label className="form-label text-start w-100">Update Founder from Group</label>
                                <select className="form-select mt-3" aria-label="Users" onChange={(e) => setMember(e.target.value)} >
                                    <option defaultChecked hidden>Select Founder</option>
                                    {users.map((value, index) => {
                                        return <option value={value.email} key={index}>{value.email}</option>
                                    })}
                                </select>
                            </div>
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-subtle" data-bs-dismiss="modal">Cancel</button>
                            <button type="button" className="btn btn-primary" onClick={editGroup}>Create</button>
                        </div>
                    </div>
                </div>
            </div>
            { /* ----------  Add Member to Group  ---------- */ }
            <div className="modal fade" id={"adduser-"+id} aria-labelledby={"adduser-"+id} aria-hidden="true">
                <div className="modal-dialog">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id={"adduser-"+id}>Add Member</h5>
                            <button type="button" className="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div className="modal-body">
                            <div className="mb-3">
                                <label className="form-label text-start w-100">Add Member to Group</label>
                                <select className="form-select mt-3" aria-label="Users" onChange={(e) => setMember(e.target.value)} >
                                    <option defaultChecked hidden>Select User</option>
                                    {users.map((value, index) => {
                                        return <option value={value.id} key={index}>{value.email}</option>
                                    })}
                                </select>
                            </div>
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-subtle" data-bs-dismiss="modal">Cancel</button>
                            <button type="button" className="btn btn-primary" onClick={addMember}>Update</button>
                        </div>
                    </div>
                </div>
            </div>
            { /* ----------  Delete Group  ---------- */ }
            <div className="modal fade" id={"deleteuser-"+id} aria-labelledby={"deleteuser-"+id} aria-hidden="true">
                <div className="modal-dialog">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id={"deleteuser-"+id}>Delete Group</h5>
                            <button type="button" className="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div className="modal-body">
                            <div className="mb-3">
                                <p>Do you want to delete the group with the name `{name}`</p>
                            </div>
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-subtle" data-bs-dismiss="modal">No, cancel!</button>
                            <button type="button" className="btn btn-danger" onClick={deleteGroup} >Yes, delete group</button>
                        </div>
                    </div>
                </div>
            </div>
        </>
    );
}

export default GroupItem;