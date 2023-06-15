import React, { useState, useEffect, useContext, useRef } from 'react'
import NavigationComponent from '../components/Navigation';
import UploadBar from '../components/UploadBar';
import SideNav from '../components/SideNav';
import Item from '../components/items/Item';
import FileInfo from '../components/FileInfo';
import AuthContext from "../components/shared/AuthContext";

const Shared = () => {
    const { getdirectories, getsubdirs } = useContext(AuthContext);  
    const [selectedfile, setSelectedFile] = useState(null);
    const [alldirectories, setAllDirectories] = useState(null);
    const [currentdirectory, setCurrentDirectory] = useState(new Array());

    function test(e) {
        if (e!==false) {
            setSelectedFile(e);
        } else {
            setSelectedFile(null);
        }
    }
    
    useEffect(() => {
        //Get Current Directory
        const path = window.location.pathname.split("/");
        const lastfolder = path[path.length-1] ==='' ? null : path[path.length-1];
        getsubdirs(lastfolder).then((result) => {
            if (result.data[0]) {
                sessionStorage.setItem("dirID", JSON.stringify(result.data[0].subdir_id===null ? null : result.data[0].subdir_id.dirID));                
            }
            setCurrentDirectory(result.data);
        }).catch((err) => { });          
    }, []);

    

    return (
        <div className='vh-100'>
            <NavigationComponent />
            <div className='row w-100 content-fill'>
                <SideNav/>
                <div className='col-8'>
                    <UploadBar />
                    {/* File List Header*/}
                    <div className='row border-bottom mb-2 mx-2'>
                        <div className='col-md-7 offset-md-1'><p className='mb-0 fw-semibold'>Name</p></div>
                        <div className='col-md-4'><p className='mb-0 fw-semibold'>Modified</p></div>
                    </div>
                    {/* File List Items*/}
                    <div className='row border-bottom m-0 mx-2'>
                        {
                            currentdirectory.map((dir, index)=>{
                                return <Item type="folder" key={index} name={dir.name} modifydate={dir.updated_at} subdir={dir.subdir_id} group={dir.group_id} id={dir.dirID} data-id="" onselected={test}/>
                            })
                        }
                    </div>
                </div>
                <div className='col-2 border-start'>
                    {
                        (selectedfile===null) ? <FileInfo /> : <FileInfo data={selectedfile} />
                    }
                </div>
            </div>
        </div>
    );
}

export default Shared;