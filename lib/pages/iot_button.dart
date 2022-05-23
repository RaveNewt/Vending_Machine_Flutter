import 'package:firebase_database/firebase_database.dart';
import 'package:flutter/material.dart';
import 'package:google_fonts/google_fonts.dart';

class ButtonIot extends StatefulWidget {
  @override
  State<ButtonIot> createState() => _ButtonIotState();
}

class _ButtonIotState extends State<ButtonIot> {
  bool on = false;
  bool on2 = true;
  int selectedIndex = -1;
  final dbR = FirebaseDatabase.instance.reference();
  @override
  Widget build(BuildContext context) {
    Widget option(
      int index,
      String titleOn,
      String titleOff,
    ) {
      return GestureDetector(
        onTap: () {
          setState(() {
            selectedIndex = index;
          });
        },
        child: Row(
          children: [
            Container(
              height: 75,
              width: 75,
              decoration: BoxDecoration(
                  borderRadius: BorderRadius.circular(20),
                  border: Border.all(
                    color: selectedIndex == index
                        ? Colors.transparent
                        : Colors.black,
                  )),
              child: TextButton(
                style: TextButton.styleFrom(
                  backgroundColor:
                      selectedIndex == index ? Colors.blue : Colors.white,
                  primary: selectedIndex == index ? Colors.blue : Colors.black,
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(20),
                  ),
                ),
                onPressed: () {
                  setState(() {
                    dbR.child('Light').set({'Switch': !on});
                    dbR.child('Light2').set({'Switch': !on2});
                    selectedIndex = index;
                    on = !on;
                    on2 = !on2;
                  });
                },
                child: selectedIndex == index
                    ? Text(
                        titleOn,
                        style: GoogleFonts.montserrat(
                            fontSize: 20, color: Colors.white),
                      )
                    : Text(
                        titleOff,
                        style: GoogleFonts.montserrat(
                          fontSize: 20,
                          color: Colors.black,
                        ),
                      ),
              ),
            ),
          ],
        ),
      );
    }

    ;
    return Scaffold(
        backgroundColor: Color(0xffFFFFFF),
        body: Padding(
          padding: const EdgeInsets.only(top: 150.0, left: 24, right: 24),
          child: Column(
            crossAxisAlignment: CrossAxisAlignment.start,
            children: [
              Center(
                  child: Image.asset(
                'assets/homeoffice1.png',
                width: 295,
              )),
              SizedBox(
                height: 60,
              ),
              Center(
                child: Text(
                  'IoT Vending Machine',
                  style: GoogleFonts.montserrat(
                    fontSize: 24,
                    fontWeight: FontWeight.bold,
                    color: Colors.black,
                  ),
                ),
              ),
              SizedBox(
                height: 60,
              ),
              Padding(
                padding: const EdgeInsets.only(left: 90.0, right: 90),
                child: Row(
                  children: [
                    option(0, 'on', '1'),
                    SizedBox(
                      width: 20,
                    ),
                    option(1, 'on', '2'),
                  ],
                ),
              ),
            ],
          ),
        ));
  }
}
