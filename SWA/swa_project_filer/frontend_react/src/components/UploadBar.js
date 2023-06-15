import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faArrowUpFromBracket, faPlus, faFileAlt, faFolderPlus } from '@fortawesome/free-solid-svg-icons';
import React, { useContext, useEffect, useState } from 'react'
import Button from 'react-bootstrap/Button';
import Modal from 'react-bootstrap/Modal';
import AuthContext from './shared/AuthContext';

const UploadBar = () => {
    const path = window.location.pathname.split("/");
    const breadcrumbs = new Array();    
    path.forEach((item, key) => {
        if (item!=="") {
            breadcrumbs.push(item);
        }
    });
    // States
    const { getusergroups, createDirectory, createfile } = useContext(AuthContext);
    const [dirname, setDirName] = useState("");
    const [uploadfiles, setUploadFiles] = useState(new Array());
    const [group, setGroup] = useState("");
    const [groups, setGroups] = useState(new Array());
    const [show, setShow] = useState(false);

    useEffect(() => {
        getusergroups().then((result) => {
            setGroups(result.data);
        }).catch((err) => {
           console.log(err); 
        });
    }, []);

    async function uploadFiles(event) {
        var target = event.target || event.srcElement;
        if (target.value.length === 0) { } else {
            console.log(event.target.files[0]);
            setUploadFiles(event.target.files); 
            let payload = {
                "filename": event.target.files[0].name,
                "storepath": "/"+path[path.length-1],
                "filesize": event.target.files[0].size,
            };
            await createfile(sessionStorage.getItem("dirID"), payload).then((result) => {
                console.log(result);
            });
            window.location.reload();
        }
    }

    //Groups & Users missing
    async function createDirectoryEvent() {
        let payload = {
            "dirname": dirname,
            "group_id": group
        };
        await createDirectory(payload, sessionStorage.getItem("dirID"));
        window.location.reload();
    }
    return (     
        <>
            <nav className='d-flex w-100 px-5 py-2 mt-2'>
                <div className='d-flex flex-column'>
                    <nav aria-label="breadcrumb">
                        <ol className="breadcrumb">
                            <li className={ path[path.length-1]!=="" ? "breadcrumb-item" : "breadcrumb-item active"}>{path[path.length-1]!=="" ? <a href="/">FILESYNC</a> : 'FILESYNC'}</li>
                            {
                                breadcrumbs.map((value, index) => {
                                    return <li key={index} className={(index==path.length-2) ? `breadcrumb-item active` : `breadcrumb-item` }>{index!==path.length-2 ? <a href="../">{value}</a> : <span className="link-dark">{value}</span>}</li>
                                })
                            }
                        </ol>
                    </nav>
                    <ul className='d-flex ms-auto list-unstyled'>
                        <li className='mx-2'>
                            <label htmlFor='fileUpload' className='btn btn-outline-primary rounded-0 px-4'>
                                <FontAwesomeIcon icon={faArrowUpFromBracket} className='me-2'/>
                                    Upload File
                            </label>
                            <input type='file' className='d-none' id="fileUpload" onInput={uploadFiles}/>
                        </li>
                        <li className='mx-2'>
                            <label htmlFor='createDir' className='btn btn-outline-info rounded-0 px-4' role='button' data-bs-toggle="modal" data-bs-target={"#createDirectory"}>
                                <FontAwesomeIcon icon={faFolderPlus} className='me-2'/>
                                    Create Folder
                            </label>
                            <input type='button' className='d-none' id="createDir"/>
                        </li>
                    </ul>
                </div>
            </nav>
            { /* ----------  Create Directory  ---------- */ }
            <div className="modal fade" id={"createDirectory"} aria-labelledby={"createDirectory"} aria-hidden="true">
                <div className="modal-dialog">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id={"createDirectory"}>Create directory</h5>
                            <button type="button" className="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div className="modal-body">
                            <div className="mb-3">
                                <label htmlFor="dirname" className="form-label text-start w-100">Directory name</label>
                                <input type="text" className="form-control py-2" onChange={(e) => setDirName(e.target.value)} id="dirname" required/>
                            </div>
                            <div className="mb-3">
                                <label className="form-label text-start w-100">Share with</label>
                                <select className="form-select mt-3" aria-label="Users" onChange={(e) => setGroup(e.target.value)} >
                                    <option defaultChecked hidden>Select Group</option>
                                    {groups.map((value, index) => {
                                        return <option value={value.id} key={index}>{value.name}</option>
                                    })}
                                </select>
                            </div>
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-subtle" data-bs-dismiss="modal">Cancel</button>
                            <button type="button" className="btn btn-primary" onClick={createDirectoryEvent}>Create</button>
                        </div>
                    </div>
                </div>
            </div>
        </>
    );
}

export default UploadBar;