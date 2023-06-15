import React, { useContext, useEffect, useState } from 'react'
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faPlus } from '@fortawesome/free-solid-svg-icons';
import NavigationComponent from '../components/Navigation';
import SideNav from '../components/SideNav';
import GroupItem from '../components/items/GroupItem';
import AuthContext from "../components/shared/AuthContext";

const Groupmanagement = () => {
    const { getallgroups, getallusers, creategroups } = useContext(AuthContext);
    const [groups, setGroups] = useState(new Array());
    const [users, setUsers] = useState(new Array());
    const [groupname, setGroupName] = useState('');
    const [member, setMember] = useState('');

    useEffect(() => {
        getallgroups().then((result) => {
            setGroups(result.data);
        });
        getallusers().then((result) => {
            setUsers(result.data);
        }).catch((err) => {
           console.log(err); 
        });
    }, []);
    async function createGroup() {
        let payload = {
            groupname: groupname,
            email: member,
        };
        await creategroups(payload).then((result) => {
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
                                <h3>Group management</h3>
                            </div>
                            <div className='d-flex ls-wide'>
                                <label htmlFor='createDir' className='btn btn-outline-primary rounded-0 px-4' role='button' data-bs-toggle="modal" data-bs-target={"#createGroup"}>
                                    <FontAwesomeIcon icon={faPlus} className='me-2'/>
                                        Create Group
                                </label>
                                <input type='button' className='d-none' id="createDir"/>
                            </div>
                        </nav>
                        <div className='row border-bottom mb-2 m-0 mx-2 py-2'>
                            <div className='col-4'><p className='mb-0 fw-semibold text-capitalize'>group name</p></div>
                            <div className='col-4'><p className='mb-0 fw-semibold text-capitalize'>founder</p></div>
                            <div className='col-3'><p className='mb-0 fw-semibold text-capitalize'>creation date</p></div>
                        </div>
                        {/* File List Items*/}
                        <div className="accordion row m-0 mx-2" id="accordion">
                            {groups.map((value, key) => {
                                return <GroupItem key={key} id={value.id} name={value.name} founder={value.founder_id.email} created={value.updated_at}/>
                            })}
                        </div>
                    </div>
                </div>
            </div>
            
            { /* ----------  Create Group  ---------- */ }
            <div className="modal fade" id={"createGroup"} aria-labelledby={"createGroup"} aria-hidden="true">
                <div className="modal-dialog">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id={"createGroup"}>Add Member</h5>
                            <button type="button" className="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div className="modal-body">
                            <div className="mb-3">
                                <label htmlFor="dirname" className="form-label text-start w-100">Group name</label>
                                <input type="text" className="form-control py-2" onChange={(e) => setGroupName(e.target.value)} id="dirname" required/>
                            </div>
                            <div className="mb-3">
                                <label className="form-label text-start w-100">Add Member to Group</label>
                                <select className="form-select mt-3" aria-label="Users" onChange={(e) => setMember(e.target.value)} >
                                    <option defaultChecked hidden>Select User</option>
                                    {users.map((value, index) => {
                                        return <option value={value.email} key={index}>{value.email}</option>
                                    })}
                                </select>
                            </div>
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-subtle" data-bs-dismiss="modal">Cancel</button>
                            <button type="button" className="btn btn-primary" onClick={createGroup}>Create</button>
                        </div>
                    </div>
                </div>
            </div>
        </>
    );
}

export default Groupmanagement;