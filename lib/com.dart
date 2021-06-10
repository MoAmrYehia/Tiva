import 'dart:typed_data';

import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:google_map_polyline/google_map_polyline.dart';
import 'package:google_maps_flutter/google_maps_flutter.dart';


import 'directions_model.dart';





class MyHomePage extends StatefulWidget {
  final BluetoothDevice server;

  const MyHomePage({Key key, this.server}) : super(key: key);
  @override
  _MyHomePageState createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {
  final Set<Polyline> polyline = {};
  // ignore: deprecated_member_use
  List<Marker>m=List<Marker>();
  Map<MarkerId, Marker> markers = {};
  // ignore: deprecated_member_use
  List<String> lat =List<String>();
  // ignore: deprecated_member_use
  List<String> lon= List<String>();
  int f=0;


  GoogleMapController _controller;
  List<LatLng> routeCoords;
  static final clientID = 0;
  BluetoothConnection connection;




  final TextEditingController textEditingController =
  new TextEditingController();
  final ScrollController listScrollController = new ScrollController();

  bool isConnecting = true;
  bool get isConnected => connection != null && connection.isConnected;

  bool isDisconnecting = false;


  GoogleMapPolyline googleMapPolyline =
  new GoogleMapPolyline(
      apiKey: "AIzaSyAyU5txJ86b25-_l0DW-IldSKGGYqQJn3M"); //AIzaSyD04c6zuCFAC2TcOJfwfZSlH9uxbLYp2Fo



  // ignore: deprecated_member_use
  List listMarkerids = List();
  Marker _origin;
  Marker _destination;
  Directions _info;

  @override
  void initState() {
    // TODO: implement initState
    super.initState();
    // getaddressPoints();

    BluetoothConnection.toAddress(widget.server.address).then((_connection) {
      print('Connected to the device');
      connection = _connection;
      setState(() {
        isConnecting = false;
        isDisconnecting = false;
      });

      connection.input.listen(_onDataReceived).onDone(() {
        // Example: Detect which side closed the connection
        // There should be `isDisconnecting` flag to show are we are (locally)
        // in middle of disconnecting process, should be set before calling
        // `dispose`, `finish` or `close`, which all causes to disconnect.
        // If we except the disconnection, `onDone` should be fired as result.
        // If we didn't except this (no flag set), it means closing by remote.
        if (isDisconnecting) {
          print('Disconnecting locally!');
        } else {
          print('Disconnected remotely!');
        }
        if (this.mounted) {
          setState(() {});
        }
      });
    }).catchError((error) {
      print('Cannot connect, exception occured');
      print(error);
    });
  }
  @override
  void dispose(){
    if (isConnected) {
      isDisconnecting = true;
      connection.dispose();
      connection = null;
    }

    super.dispose();
  }
  @override
  Widget build(BuildContext context) {
    /* markers.addAll([
      Marker(markerId: MarkerId('value'),
      position: LatLng(30.063397,31.281174),
      infoWindow: InfoWindow(title: "Abbasya"))
    ]);*/
    return Scaffold(
        body: Stack(
          alignment: Alignment.center,
          children: [
            GoogleMap(
              myLocationButtonEnabled: true,

              onMapCreated: onMapCreated,
              // polylines: polyline,
              initialCameraPosition:
              CameraPosition(target: LatLng(30.064101, 31.279242), zoom: 18.0),
              markers:Set.of(m),//Set.of(markers.values),//Set.of(m),
              /*{
                if(_origin !=null)
                  _origin,
              if(_destination !=null)
                _destination
      },*/
              onTap: _addMarker,
              polylines: {
                if(_info != null)
                  Polyline(polylineId: PolylineId('overview_polyline'),
                    color: Colors.red,
                    width: 5,
                    points: _info.polylinePoints.map((e) =>
                        LatLng(e.latitude, e.longitude)).toList(),
                  ),
              },

              onLongPress: _addMarker,
              mapType: MapType.normal,

            ),
            if(_info != null)
              Positioned(
                top: 20.0,
                child: Container(
                  padding: const EdgeInsets.symmetric(
                    vertical: 6.0,
                    horizontal: 12.0,
                  ),
                  decoration: BoxDecoration(
                    color: Colors.yellowAccent,
                    borderRadius: BorderRadius.circular(20.0),
                    boxShadow: const[
                      BoxShadow(
                        color: Colors.black26,
                        offset: Offset(0, 2),
                        blurRadius: 6.0,
                      )
                    ],
                  ),
                  child: Text(
                    '${_info.totalDistance},${_info.totalDuration}',
                    style: const TextStyle(
                      fontSize: 18.0,
                      fontWeight: FontWeight.w600,
                    ),
                  ),
                ),
              ),

          ],
        ));
  }

  void _addMarker(LatLng pos) async {
    if(lat[f]!=null &&lon[f]!=null)
    {
      setState(() {

        int a=0;
        if(lat.length<=lon.length)
          a=lat.length;
        else
          a=lon.length;

        for(int i=0;i<a;i++) {
          m.add(Marker(markerId: MarkerId(f.toString()),
              position: LatLng(double.parse(lat[f]), double.parse(lon[f])),
              icon: BitmapDescriptor.defaultMarkerWithHue(
                  BitmapDescriptor.hueCyan)));
          ;
          f++;
        }
      });

    }

/*
    if (_origin == null || (_origin != null && _destination != null)) {
      setState(() {
        _origin = Marker(markerId: MarkerId('origin'),
          infoWindow: const InfoWindow(title: 'origin'),
          icon: BitmapDescriptor.defaultMarkerWithHue(
              BitmapDescriptor.hueGreen),
          position: pos,
        );
        _destination = null;
        _info = null;
      });
    }
    else {
      setState(() {
        _destination = Marker(markerId: MarkerId('destination'),
          infoWindow: const InfoWindow(title: 'Destination'),
          icon: BitmapDescriptor.defaultMarkerWithHue(BitmapDescriptor.hueBlue),
          position: pos,
        );
      });

      final directions = await DirectionRepository().getDirections(
          origin: _origin.position, destination: pos);
      setState(() => _info = directions);
    }*/
  }



  void _onDataReceived(Uint8List data) {
    // Allocate buffer for parsed data
    //print("before");
    //print(data);
    int backspacesCounter = 0;
    data.forEach((byte) {
      if (byte == 8 || byte == 127) {
        backspacesCounter++;
      }
    });
    Uint8List buffer = Uint8List(data.length - backspacesCounter);
    int bufferIndex = buffer.length;

    // Apply backspace control character
    backspacesCounter = 0;
    for (int i = data.length - 1; i >= 0; i--) {
      if (data[i] == 8 || data[i] == 127) {
        backspacesCounter++;
      } else {
        if (backspacesCounter > 0) {
          backspacesCounter--;
        } else {
          buffer[--bufferIndex] = data[i];
        }
      }
    }

    // Create message if there is new line character
    String dataString = String.fromCharCodes(buffer);
    print("after");
    print(dataString);
    for(int i=0;i<dataString.length;i++)
    {

      if(dataString[i]=='T')
      {
        lat.add(dataString.substring(i+1,i+10));
        print("lat");
        print(lat);
      }
      if(dataString[i]=='N') {
        lon.add(dataString.substring(i+1,i+10));
        print("lon");
        print(lon);
      }

    }





  }

  void onMapCreated(GoogleMapController controller) {

    MarkerId markerId1 = MarkerId("1");
    MarkerId markerId2 = MarkerId("2");
    MarkerId markerId3 = MarkerId("3");
    listMarkerids.add(markerId1);
    listMarkerids.add(markerId2);
    listMarkerids.add(markerId3);
    Marker marker1 = Marker(markerId: markerId1,
        position: LatLng(30.063397, 31.281174),
        icon: BitmapDescriptor.defaultMarkerWithHue(BitmapDescriptor.hueCyan));
    Marker marker2 = Marker(markerId: markerId2,
        position: LatLng(30.073397, 31.261174),
        icon: BitmapDescriptor.defaultMarkerWithHue(BitmapDescriptor.hueCyan));
    Marker marker3 = Marker(markerId: markerId3,
        position: LatLng(30.043397, 31.241174),
        icon: BitmapDescriptor.defaultMarkerWithHue(BitmapDescriptor.hueCyan));


    setState(() {
      _controller = controller;
      m.add( Marker(markerId: MarkerId(f.toString()),
          position: LatLng(double.parse(lat[f]), double.parse(lon[f]) ),
          icon: BitmapDescriptor.defaultMarkerWithHue(BitmapDescriptor.hueAzure)));;

      f++;
      markers[markerId1] = marker1;
      markers[markerId2] = marker2;
      markers[markerId3] = marker3;


      polyline.add(Polyline(
          polylineId: PolylineId('route1'),
          visible: true,
          points: routeCoords,
          width: 4,
          color: Colors.blue,
          startCap: Cap.roundCap,
          endCap: Cap.buttCap));
    });
  }
}





/*
  void _onAddMarkerButtonPressed(){
    setState(() {
      _markers.add(Marker(markerId: _lastMapPosition.toString(),
      position: _lastMapPosition,
      icon: BitmapDescriptor.defaultMarker,));
      _polyline.add(Polyline(polylineId: PolylineId(_lastMapPosition.toString()),
        visible: true,
        points: latlng,
        color: Colors.blue,));
    });

  }
}*/
