void initCalibration()
{
    int m_o = 25; //origin 
    int m_x = 27; // x
    int m_y = 28; // y
    int m_z = 26; // z
    system_calibrated = false;
    Vector3d temp_marker;
    //calibration_offset = Vector3d(0, 0, 0);
    origin_raw = Vector3d(0, 0, 0);

    referenceM << 160.0, 0.0, 0.0,
        0.0, 160.0, 0.0,
        0.0, 0.0, 160.0;

    MatrixXd temp_calibrationM(3, 3);

    int num_measure = 30;
    int invisibleFrameN = 0;

    for (int i = 0; i < num_measure; i++) {
        optotrak.updateMarkers();


        if (isVisible(markers[m_o].p) && isVisible(markers[m_x].p) && isVisible(markers[m_y].p) && isVisible(markers[m_z].p)) {
            for (int j = 0; j < 3; j++) {
                temp_calibrationM(0, j) = temp_calibrationM(0, j) + markers.at(m_x).p[j];
                temp_calibrationM(1, j) = temp_calibrationM(1, j) + markers.at(m_y).p[j];
                temp_calibrationM(2, j) = temp_calibrationM(2, j) + markers.at(m_z).p[j];
            }
            origin_raw = origin_raw + markers.at(m_o).p;

            /*
            temp_marker = markers.at(m_x).p; // markers 2,3,4 correspond to x,y,z
            for (int j = 0; j < 3; j++) // coordinates index
                temp_calibrationM(0, j) = temp_calibrationM(0, j) + temp_marker(j); // this inputs the markers vectors rowwise!

            temp_marker = markers.at(m_y).p; // markers 2,3,4 correspond to x,y,z
            for (int j = 0; j < 3; j++) // coordinates index
                temp_calibrationM(1, j) = temp_calibrationM(1, j) + temp_marker(j); // this inputs the markers vectors rowwise!

            temp_marker = markers.at(m_z).p; // markers 2,3,4 correspond to x,y,z
            for (int j = 0; j < 3; j++) // coordinates index
                temp_calibrationM(2, j) = temp_calibrationM(2, j) + temp_marker(j); // this inputs the markers vectors rowwise!
    */
        }
        else {
            invisibleFrameN++;
        }
    }


    temp_calibrationM = temp_calibrationM / double(num_measure - invisibleFrameN);

    calibrationM = temp_calibrationM.transpose(); // transpose so that markers vectors are ordered columnwise
    origin_raw = origin_raw / double(num_measure - invisibleFrameN);

    // translate calibrationM to become calibrationM_tr
    MatrixXd origin_rep(3, 3);
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            origin_rep(row, col) = origin_raw(row);

    calibrationM_tr = calibrationM - origin_rep;

    rotationM = referenceM * calibrationM_tr.inverse();
    system_calibrated = true;


}



void online_calibrate_markers()
{


    for (int i = 1; i <= OPTO_NUM_MARKERS; i++)
    {

        markers.at(i).p -= origin_raw;
        markers.at(i).p = rotationM * markers.at(i).p - calibration_offset; //Vector3d(364, 564.25, 679)

    }
}


// run a method to define a vector that holds marker positions 
void updateTheMarkers()
{
    // this gets called every frame in idle()
    optotrak.updateMarkers();
    markers = optotrak.getAllMarkers();
    if (system_calibrated)
        online_calibrate_markers();
}
