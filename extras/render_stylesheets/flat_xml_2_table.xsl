<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<!--
Simple XSLT stylesheet to transform "flat" XML into simple HTML table markup.
Can be used as the RENDER_STYLESHEET datastream for collections or individual
objects managed by the Islandora Simple XML Solution Pack. Elements must have
an 'displayLabel' attribute in order for the field to get a human-readable label.
-->

<!-- Select the root element. -->
  <xsl:template match="/*">
    <div>
      <table>
        <xsl:apply-templates/>
      </table>
    </div>
  </xsl:template>

  <!-- Select all children of the root node. Human-readable field names come from the @displayLabel attribute. -->
  <xsl:template match="*">
    <tr><th><xsl:value-of select="@displayLabel"/></th><td><xsl:value-of select="."/></td></tr>
  </xsl:template>

</xsl:stylesheet>

