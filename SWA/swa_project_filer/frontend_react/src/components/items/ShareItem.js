import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faUser, faUserGroup } from '@fortawesome/free-solid-svg-icons';
import { v4 as uuidv4 } from 'uuid';
import React, { useState } from 'react'

const ShareItem = ({name, type, selected=false}) => {   
    const [checked, setChecked] = useState(selected);
    const id = uuidv4();
    return (  
        <>
            <label htmlFor={id} className='col-12 row m-0 mb-1 py-2 user-select-none' data-item-id={name}>
                <div className='col-1 d-flex align-items-center justify-content-center'>
                    <input type='checkbox' className='form-check-input' name="selection" id={id} checked={checked} onChange={()=>setChecked(!checked)}/>
                </div>
                <div className='col-7 d-flex align-items-center'>
                    {type === "group" ? (
                        <span className="avatar p-2 text-blue-200 bg-blue-50"><FontAwesomeIcon icon={faUserGroup}/></span>
                    ) : (
                        <span className="avatar p-2 text-blue-200 bg-blue-50"><FontAwesomeIcon icon={faUser}/></span>
                    )}
                    <p className='ms-3 text-dark mb-0'>{name}</p>
                </div>
            </label>
        </>
    );
}

export default ShareItem;