import React, { useContext, useState } from 'react'
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faEllipsis, faTrashCan, faEdit } from '@fortawesome/free-solid-svg-icons';
import { Dropdown } from 'react-bootstrap';
import dayjs from "dayjs";
import AuthContext from "../shared/AuthContext";

const MemberItem = ({index, fname, lname, email, dob, role, groupid}) => {
    const { removeuserfromgroups } = useContext(AuthContext);
    const [firstname, setFirstName] = useState(fname);
    const [lastname, setLastName] = useState(lname);
    const [email_, setEmail] = useState(email);
    const [dob_, setDob] = useState(dob);
    const [role_, setRole] = useState(role);
    const [groupid_, setGroupId] = useState(groupid);

    async function deletememberfromgroup() {
        await removeuserfromgroups(index, groupid).then((result) => {
            console.log(result);
        }).catch((err) => {
            
        });
        window.location.reload();
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
                <div className='col-1 d-flex align-items-center p-0'>
                    <button className='ms-3 text-red-200 btn mb-0 text-capitalize' onClick={deletememberfromgroup}><FontAwesomeIcon icon={faTrashCan} /> Delete</button>
                </div>
            </div>
        </>
    );
}

export default MemberItem;