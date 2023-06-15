import React, {useState} from 'react'
import NavigationComponent from '../components/Navigation';
import UploadBar from '../components/UploadBar';
import SideNav from '../components/SideNav';
import Item from '../components/items/Item';
import FileInfo from '../components/FileInfo';

const Home = () => {
    const [selectedfile, setSelectedFile] = useState([]);

    function test(e) {
        if (e!==false) {
            setSelectedFile(e);
        } else {
            setSelectedFile([]);
        }
    }
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
                        <Item type="folder" name='test1' date="02.06.2023" onselected={test}/>
                        <Item type="folder" name='test2' date="02.06.2023" onselected={test}/>
                        <Item type="file" name='test3' date="02.06.2023" onselected={test}/>
                    </div>
                </div>
                <div className='col-2 border-start'>
                    {
                        (selectedfile.length===0) ? <FileInfo /> : <FileInfo data={selectedfile} />
                    }
                </div>
            </div>
        </div>
    );
}

export default Home;