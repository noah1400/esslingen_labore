import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faFileAlt, faFolder, faEllipsis, faTrashCan, faICursor } from '@fortawesome/free-solid-svg-icons';
import { Dropdown } from 'react-bootstrap';
import { v4 as uuidv4 } from 'uuid';
import React, { useContext, useRef, useState } from 'react'
import dayjs from "dayjs";
import AuthContext from '../shared/AuthContext';

const Item = ({type, name, modifydate, subdir, group, id, onselected}) => {
    const UUIDid = uuidv4();
    const { deletefile } = useContext(AuthContext);
    function selectRow(e){
        if (e.target.checked===true) {
            e.target.parentNode.parentNode.classList.add('selected-row');
            let fileData = {
                id: id,
                name: name,
                date: modifydate,
                type: type,
                subdir: subdir,
                group: group
            };
            onselected(fileData);
        } else {
            e.target.parentNode.parentNode.classList.remove('selected-row');
            onselected(false);
        }
    }

    async function removeFile() {
        await deletefile(id).then((result) => {
            console.log(result);
        }).catch((err) => {
            console.log(err);
        });
    }

    return (
        <>
            <label htmlFor={UUIDid} className='col-12 row m-0 mb-1 py-2 user-select-none' data-item-id={name}>
                <div className='col-1 d-flex align-items-center justify-content-center'>
                    <input type='radio' className='form-check-input' name="selection" value={UUIDid} id={UUIDid} onChange={(event)=>selectRow(event)}/>
                </div>
                <div className='col-7 d-flex align-items-center'>
                    {type === "folder" ? (
                        <FontAwesomeIcon icon={faFolder} size='2x' color='#5272ff'/>
                    ) : (
                        <FontAwesomeIcon icon={faFileAlt} size='2x' color='#5272ff'/>
                    )}
                    <a href={`${(window.location.pathname==="/") ? "." : window.location.pathname}/${name}`} className='ms-3 text-dark text-decoration-none'>{name}</a>
                </div>
                <div className='col-4 d-flex align-items-center'>
                    <p className='mb-0'>{dayjs(modifydate).format("DD.MM.YYYY")}</p>
                </div>
                {/*
                <div className='col-1 d-flex align-items-center'>
                    
                    <Dropdown>
                      <Dropdown.Toggle className="bg-white border-0 p-0" variant='light' id="dropdown-basic">
                        <span className='btn rounded-0 btn-subtle'><FontAwesomeIcon icon={faEllipsis}/></span>
                      </Dropdown.Toggle>

                      <Dropdown.Menu className='rounded-0'>
                        <Dropdown.Item href="#" className='text-neutral-700'><FontAwesomeIcon icon={faICursor}/> Rename</Dropdown.Item>
                        <Dropdown.Item href="#" className='text-red-200' onClick={removeFile}><FontAwesomeIcon icon={faTrashCan}/> Delete</Dropdown.Item>
                      </Dropdown.Menu>
                    </Dropdown>
                </div>
                    */}
            </label>
        </>
    );
}

export default Item;