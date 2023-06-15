import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faFileAlt, faFolder, faEllipsis } from '@fortawesome/free-solid-svg-icons';
import React from 'react'
import { v4 as uuidv4 } from 'uuid';

const Item = ({name, type, date, onselected}) => {
    function selectRow(e){
        console.log(e.target.selected);
        if (e.target.checked===true) {
            e.target.parentNode.parentNode.classList.add('selected-row');
            let fileData = {
                name: name,
                date: date,
                type: type
            };
            onselected(fileData);
        } else {
            e.target.parentNode.parentNode.classList.remove('selected-row');
            onselected(false);
        }
    }
    const id = uuidv4();
    return (  
        <>
            <label htmlFor={id} className='col-12 row m-0 mb-1 py-2 user-select-none' data-item-id={name}>
                <div className='col-1 d-flex align-items-center justify-content-center'>
                    <input type='checkbox' className='form-check-input' name="selection" id={id} onChange={selectRow}/>
                </div>
                <div className='col-7 d-flex align-items-center'>
                    {type === "folder" ? (
                        <FontAwesomeIcon icon={faFolder} size='2x' color='#5272ff'/>
                    ) : (
                        <FontAwesomeIcon icon={faFileAlt} size='2x' color='#5272ff'/>
                    )}
                    <a href={`/${name}`} className='ms-3 text-dark text-decoration-none'>{name}</a>
                </div>
                <div className='col-3 d-flex align-items-center'>
                    <p className='mb-0'>{date}</p>
                </div>
                <div className='col-1 d-flex align-items-center'>
                    <button className='btn rounded-0'><FontAwesomeIcon icon={faEllipsis}/></button>
                </div>
            </label>
        </>
    );
}

export default Item;