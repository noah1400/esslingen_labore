import React from 'react'
import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { faFolder, faCircleInfo, faPlus } from '@fortawesome/free-solid-svg-icons';
import ShareItem from './items/ShareItem';
import dayjs from 'dayjs';

const FileInfo = (data) => {
    return (
        (data.data!==undefined) ? 
        <>
            <p className='mt-4 ms-2'><FontAwesomeIcon icon={faCircleInfo} className='me-2' color='#202020'/> Info</p>
            <FontAwesomeIcon icon={faFolder} size='8x' className='mt-5 d-flex justify-align-center w-100 filter-shadow-sm' color='#5272ff'/>
            <p className='mt-5 ms-2 mb-1 fw-semibold'>Properties</p>
            <div className='row mt-1 ms-2'>
                <div className='col-4 p-0'>Modified</div>
                <div className='col-8'>{dayjs(data.data.date).format("DD.MM.YYYY")}</div>
            </div>
            <div className='row mt-1 ms-2'>
                <div className='col-4 p-0'>Name</div>
                <div className='col-8'>{data.data.name}</div>
            </div>
            <p className='mt-5 mb-1 fw-semibold ms-2'>Shared with</p>
            <div className='row mt-1 ms-2'>
                <div className='col-8 p-0 d-flex justify-align-center'>
                    <div className="avatar-stack">
                        {
                            /*
                                <div className="avatar-item">
                                    <span className="avatar text-bg-danger">H</span>
                                </div>
                                <div className="avatar-item">
                                    <span className="avatar text-bg-primary">U</span>
                                </div>
                                <div className="avatar-item">
                                    <span className="avatar text-bg-secondary">OP</span>
                                </div>
                                <div className="avatar-item">
                                    <span className="avatar">+6</span>
                                </div>
                            */
                        }
                    </div>
                </div>
                <div className='col-4'>
                    <button className='avatar p-2 border-0 bg-dark text-light' data-bs-toggle="modal" data-bs-target="#sharedwith"><FontAwesomeIcon icon={faPlus}/></button>
                </div>
            </div>
            { /* ----------  Add User to Folder  ---------- */ }
            <div className="modal fade" id="sharedwith" aria-labelledby="exampleModalLabel" aria-hidden="true">
                <div className="modal-dialog">
                    <div className="modal-content">
                        <div className="modal-header">
                            <h5 className="modal-title" id="exampleModalLabel">Share <i>{data.data.name}</i> with users</h5>
                            <button type="button" className="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                        </div>
                        <div className="modal-body">
                            <div className='row mt-0'>
                                <div className='col-12'><p className='mt-5 mb-1 fw-semibold ms-2'>Groups</p></div>
                                <div className='col-12'>
                                    <ShareItem name="Group1" type="group" selected/>
                                    <ShareItem name="Group1" type="group" />
                                    <ShareItem name="Group1" type="group" selected/>
                                </div>
                                <div className='col-12'><p className='mt-5 mb-1 fw-semibold ms-2'>Users</p></div>
                                <div className='col-12'>
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                    <ShareItem name="Group1" type="user" />
                                </div>
                            </div>
                        </div>
                        <div className="modal-footer">
                            <button type="button" className="btn btn-subtle" data-bs-dismiss="modal">Cancel</button>
                            <button type="button" className="btn btn-primary">Confirm</button>
                        </div>
                    </div>
                </div>
            </div>
        </> : 
        <>
            <p className='mt-4 ms-2'><FontAwesomeIcon icon={faCircleInfo} className='me-2' color='#202020'/> Info</p>
            <FontAwesomeIcon icon={faFolder} size='8x' className='mt-5 d-flex justify-align-center w-100 filter-shadow-sm' color='#5272ff'/>
        </>
    );
}

export default FileInfo;