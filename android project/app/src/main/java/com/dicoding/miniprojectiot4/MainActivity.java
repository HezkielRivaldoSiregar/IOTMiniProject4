package com.dicoding.miniprojectiot4;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.ToggleButton;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    String ldr;
    TextView tvLDR;
    ToggleButton tbOnOff;
    ToggleButton tbOtomatisasi;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tbOnOff = findViewById(R.id.tbOnOff);
        tbOtomatisasi = findViewById(R.id.tbOtomatisasi);
        tvLDR = findViewById(R.id.tvLDR);

        DatabaseReference dref = FirebaseDatabase.getInstance().getReference();
        dref.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(DataSnapshot dataSnapshot) {
                ldr = dataSnapshot.child("/miniProject4/ldr").getValue().toString();
                tvLDR.setText(ldr);
            }

            @Override
            public void onCancelled( DatabaseError databaseError) {

            }
        });

        tbOtomatisasi.setOnCheckedChangeListener(((buttonView, isChecked) -> {
            if(isChecked){
                DatabaseReference otomatisasi = FirebaseDatabase.getInstance().getReference("/miniProject4/otomatisasi");
                otomatisasi.setValue(1);
            }else{
                DatabaseReference otomatisasi = FirebaseDatabase.getInstance().getReference("/miniProject4/otomatisasi");
                otomatisasi.setValue(0);
            }
        }));

        tbOnOff.setOnCheckedChangeListener(((buttonView, isChecked) -> {
            if(isChecked){
                DatabaseReference button = FirebaseDatabase.getInstance().getReference("/miniProject4/button");
                button.setValue(1);
            }else{
                DatabaseReference button = FirebaseDatabase.getInstance().getReference("/miniProject4/button");
                button.setValue(0);
            }
        }));


    }
}