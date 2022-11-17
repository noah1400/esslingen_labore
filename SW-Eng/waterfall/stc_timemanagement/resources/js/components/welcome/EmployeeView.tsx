import React, { useEffect, useState } from 'react';
import Calendar from 'react-calendar';
import { Chart } from "react-google-charts";
import 'react-calendar/dist/Calendar.css';
import Axios from '../../axios';

export const data = [
    ["Status", "Days"],
    ["Not yet Applied", 25],
    ["Appling", 1],
    ["Applied", 30],
];

export const options = {
    legend: "none",
    pieSliceText: "label",
};

export default function Employee() {
    type EntryProps = {
        id: number
        user_id: number
        date: string
        start_time: string
        end_time: string
        break_time: string
        hours_target: string
        hours_as_is: string
        absence_id: number
    }

    const initEntryData = {
        id: -1,
        user_id: -1,
        date: "",
        start_time: "",
        end_time: "",
        break_time: "",
        hours_target: "",
        hours_as_is: "",
        absence_id: -1
    }
    const [value, onChange] = useState(new Date());
    const [entry, setEntry] = useState<EntryProps>(initEntryData);
    function calcFlexTime() {
        if (entry.id === -1) {
            return 0 + " min";
        } else {
            if (entry.hours_target === null || entry.hours_target === ""
                || entry.hours_as_is === null || entry.hours_as_is === "") {
                return 0;
            } else {
                var tzoffset = (new Date()).getTimezoneOffset() * 60000; //offset in milliseconds
                let as_is = (new Date(new Date("1970-01-01T" + entry.hours_as_is + "Z").getMilliseconds() - tzoffset));
                // create date of format HH:MM:SS with entry.hours_target
                let target = (new Date(new Date("1970-01-01T" + entry.hours_target + "Z").getMilliseconds() - tzoffset));


                let diff = as_is.getTime() - target.getTime();
                let hours = diff / (1000 * 60 * 60);
                return hours + " h";
            }
        }
    }
    function calcBreakTime() {
        if (entry.id === -1) {
            return 0 + " min";
        } else {
            if (entry.break_time === null || entry.break_time === "") {
                return 0 + " min";
            } else {
                let break_time = (new Date(new Date("1970-01-01T" + entry.break_time + "Z").getMilliseconds()));
                let hours = break_time.getHours();
                if (hours < 1) {
                    let minutes = break_time.getMinutes();
                    return minutes + " min";
                } else {
                    return hours + " h";
                }
            }
        }
    }


    function onValueChange(value) {
        var tzoffset = (new Date()).getTimezoneOffset() * 60000; //offset in milliseconds
        var localISOTime = (new Date(value - tzoffset)).toISOString().slice(0, -1);
        // convert value to format YYYY-MM-DD
        const date = localISOTime.split('T')[0];
        // fetch entry data
        const fetchEntryData = async () => {
            const result = await Axios.get(
                `/api/v1/user/entry/${date}`
            );
            setEntry(result.data[0] || initEntryData);
        }
        fetchEntryData();

        onChange(value);
    }

    useEffect(() => {

    });
    return (
        <div className="min-h-screen pt-5 bg-gray-100">
                <div className="mx-auto max-w-7xl grid grid-cols-3 gap-x-5">
                    <div className="bg-white border border-gray-400 col-span-1">
                        <p className="px-2 py-2 mx-4 my-4 text-xl text-center text-black border-2 border-gray-400">
                            Flex Time: <span className="text-green-700">+2 hr</span>
                        </p>
                        <div className="mx-4 my-4 border-2 border-gray-400">
                            <h2 className="mt-5 text-xl text-center">Vacation days</h2>
                            <h3 className="text-xl text-center">25/1/30</h3>
                            <Chart
                                chartType="PieChart"
                                options={options}
                                data={data}
                                height={"400px"} />
                        </div>
                    </div>

                    <div className="flex items-center justify-center px-2 bg-white border border-gray-400 col-span-2">
                        <div className="px-4 py-4 grid gap-x-4 grid-cols-5">
                            <div className="flex flex-col justify-between col-span-2">
                                <div>
                                    <h2 className="text-xl">{value.toDateString()}</h2>
                                    <p className="mt-2 text-md">Office hour: {entry.id !== -1 ? entry.start_time + ' - ' + entry.end_time : ''}</p>
                                    <p className="mt-2 text-md">Flex Time: {calcFlexTime()}</p>
                                    <p className="mt-2 text-md">Break Time: {calcBreakTime()}</p>
                                </div>
                                <div className="flex flex-col justify-center">
                                  <button
                                    className="py-2 my-2 text-white bg-blue-500"
                                    onClick={() => {
                                      alert('We have not yet implemented this feature')
                                    }}
                                  >Edit Entry</button>
                                  <button
                                    className="py-2 my-2 text-white bg-blue-600"
                                    onClick={() => {
                                      alert('We have not yet implemented this feature')
                                    }}
                                  >Ask for Leave</button>
                                </div>
                            </div>
                            <div className="col-span-3">
                                <Calendar
                                    onChange={onValueChange}
                                    value={value} />
                            </div>
                        </div>
                    </div>
                </div>
            </div>
    );
}

